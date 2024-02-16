#include "mqtti.h"
#include <QUrl>
#include <QEventLoop>
#include <QMqttClient>
#include <QSet>
#include <QTextStream>
#include <QNetworkProxy>
#include <QDateTime>
#include <QUuid>

const auto MAGIC = R"(ÅÄÖ)";
const auto MAGIC_SIZE = sizeof(MAGIC) - 2;
static_assert(MAGIC_SIZE == 6, "Look at Magic!");
const auto HISTORY_MAX = 256;
const auto UUID_SIZE = 16;
const auto DEFAULT_MQTT_PORT = 1883;
enum {HISTORY_TOPIC, HISTORY_TIME, HISTORY_MESSAGE, HISTORY_DIR};
enum class Direction : quint8 {In, Out};
enum Kind : quint8 {Message, Binary};

#define ERR_TRUNCATED tr("Truncated message")
#define ERR_CORRUPTED tr("Corrupted message")

template<typename T>
static std::optional<T> read(unsigned& pos, const QByteArray& arr) {
    if(arr.size() - pos < static_cast<int>(sizeof(T)))
        return std::nullopt;
    const auto data = arr.mid(pos, sizeof(T));
    const auto v = reinterpret_cast<const T*>(data.constData());
    pos += sizeof(T);
    return std::make_optional(*v);
}

template<>
std::optional<QUuid> read(unsigned& pos, const QByteArray& arr) {
    if(arr.size() - pos < UUID_SIZE)
        return std::nullopt;
    const auto uuid = QUuid::fromRfc4122(arr.mid(pos, UUID_SIZE));
    pos += UUID_SIZE;
    return std::make_optional(uuid);
}

template<typename T>
void write(QByteArray& bytes, const T& data) {
    bytes.append(reinterpret_cast<const char*>(&data), sizeof(T));
}
template<>
void write(QByteArray& bytes, const QByteArray& data) {
    bytes.append(data);
}


static QByteArray to_bytes(const QUuid& uid) {
    return uid.toRfc4122();
}

static
QByteArray magic() { // strip off trailing zero
    return QByteArray::fromRawData(MAGIC, static_cast<qsizetype>(MAGIC_SIZE));
}

class Mqtti::Private {
public:
    using HistoryRecord = std::tuple<QString, QDateTime, QString, Direction>;
    using History = QHash<QUuid, HistoryRecord>;
    using HistoryList = QList<QUuid>;
    using Binary = QPair<QString, QByteArray>;
    Private(Mqtti* mqtti) {
        // on error
        QObject::connect(&m_client, &QMqttClient::errorChanged, mqtti, [mqtti](const auto& err) {
            QString str;
            QTextStream stream(&str);
            stream << err;
            emit mqtti->error(str);
        });
        // on subscription
        QObject::connect(&m_client, &QMqttClient::messageReceived, mqtti, [mqtti, this](const auto& msg, const auto& tpc) {
            const auto topic = tpc.name();
            if(!m_subscriptions.contains(topic)) {
                qDebug() << topic << "subscrioption has expired";
                return;
            }
            if(msg.size() >  static_cast<qsizetype>(MAGIC_SIZE) &&  msg.mid(0, MAGIC_SIZE) == magic()) {
                unsigned pos = MAGIC_SIZE;
                mqtti->handleMessage(pos, topic, msg);
            } else {
                mqtti->handleRawMessage(topic, msg);
            }
        });
        // restore subscriptions
        QObject::connect(&m_client, &QMqttClient::connected, [this](){
            for(const auto& topic : m_subscriptions) {
                m_client.subscribe(topic);
            }
        });

    }

    bool publish(const QString& topic, const QByteArray& msg) {
        const QMqttTopicName t{topic};
        if(!t.isValid() || topic.isEmpty())
            return false;
        if(connect() && m_client.state() == QMqttClient::ClientState::Connected) {
            m_client.publish(t, msg);
            return true;
        }
        return false;
    }

    bool subscribe(const QMqttTopicFilter& topic) {
        if(connect() && m_client.state() == QMqttClient::ClientState::Connected) {
            m_client.subscribe(topic);
            m_subscriptions.insert(topic.filter());
            return true;
        }
        return false;
    }

    bool unSubscribe(const QMqttTopicFilter& topic) {
        connect();
        m_client.unsubscribe(topic);
        auto it = m_subscriptions.find(topic.filter());
        if(it != m_subscriptions.end())
            m_subscriptions.erase(it);
        return true;
    }

    QStringList subscriptions() const {
        QStringList subs(m_subscriptions.begin(), m_subscriptions.end());
        subs.sort();
        return subs;
    }

    QUrl server() const {
       QUrl url;
       url.setHost(m_client.hostname());
       url.setPort(m_client.port());
       return url;
    }

    bool setServer(const QUrl& serverName) {
        if(m_client.state() != QMqttClient::ClientState::Disconnected)
            return false; // only when disconnected!
        const auto host = serverName.host();
        if(host.isEmpty())
            return false;
        m_client.setHostname(host);
        const auto port = (serverName.port() < 0 || serverName.port() > 65535)  ? DEFAULT_MQTT_PORT : serverName.port();
        m_client.setPort(port);
        Q_ASSERT(server().host() == serverName.host());
        return true;
    }

    HistoryRecord history(int index) const {
        return m_historyData[m_historyList[index]];
    }

    int historySize() const {
        return m_historyData.size();
    }

    bool contains(const QUuid& id) const {
        return m_historyData.contains(id);
    }

    void addHistory(const QUuid& uid, const QString& topic, const QString& message, const Direction& adir) {
        if(historySize() > HISTORY_MAX) {
            const auto fst = m_historyList.first();
            m_historyData.remove(fst);
            m_historyList.pop_front();
        }
        m_historyData.insert(uid, {topic, QDateTime::currentDateTimeUtc(), message, adir});
        m_historyList.append(uid);
    }

    int storeBinary(const QString& name, QByteArray&& bytes) {
        const auto count = binaryCount();
        m_binaries.push_back({name, std::move(bytes)});
        return count;
    }

    int binaryCount() const {
        return m_binaries.size();
    }

    void deleteBinary(int pos) {
        m_binaries.removeAt(pos);
    }

    const Binary& binary(int pos) const {
        return m_binaries.at(pos);
    }

private:
    bool connect() {
        const auto await = [&]() {
            QEventLoop loop;
            bool is_ok = true;
            QObject::connect(&m_client, &QMqttClient::connected, &loop, &QEventLoop::quit);
            QObject::connect(&m_client, &QMqttClient::errorChanged, &loop, [&loop, &is_ok](auto err){
                qDebug() << "Connection failed" << err;
                is_ok = false;
                loop.quit();
            });
            QNetworkProxy::setApplicationProxy(QNetworkProxy::NoProxy);
            m_client.connectToHost();
            loop.exec();
            return is_ok;
        };
        if(m_client.state() == QMqttClient::ClientState::Disconnected) {
            if(!await())
                return false;
        }
        if(m_client.state() == QMqttClient::ClientState::Connecting) {
            if(!await())
                return false;
        }
        return true;
    }

private:
    QMqttClient m_client;
    QSet<QString> m_subscriptions;
    QVector<Binary> m_binaries;
    History m_historyData;
    HistoryList m_historyList;
};


Mqtti::Mqtti(QObject *parent)
    : QObject{parent}, m_private{new Private{this}} {

}

Mqtti::~Mqtti() {}

bool Mqtti::publishRaw(const QString& topic, const QByteArray& msg) {
    if(!m_private->publish(topic, msg))
        return false;
    return true;
}


bool Mqtti::publishMessage(const QString& topic, const QString& message) {
    QByteArray msg;
    write(msg, magic());
    Q_ASSERT(msg.size() == MAGIC_SIZE);
    const auto uid = QUuid::createUuid();
    write(msg, to_bytes(uid));
    Q_ASSERT(msg.size() == MAGIC_SIZE + UUID_SIZE);
    write(msg, Kind::Message);
    Q_ASSERT(msg.size() == MAGIC_SIZE + UUID_SIZE + 1);
    const auto bytes = message.toUtf8();
    write<uint32_t>(msg, bytes.size());
    write(msg, bytes);
    if(!m_private->publish(topic, msg))
        return false;
    m_private->addHistory(uid, topic, message, Direction::Out);
    emit recordsChanged();
    return true;
}

bool Mqtti::publishBinary(const QString& topic, const QString& name, const QByteArray& bytes) {
    QByteArray msg;
    write(msg, magic());
    const auto uid = QUuid::createUuid();
    write(msg, to_bytes(uid));
    write(msg, Kind::Binary);
    write(msg, static_cast<quint32>(name.toUtf8().size()));
    write(msg, name.toUtf8());
    write(msg, static_cast<quint32>(bytes.size()));
    write(msg, bytes);
    if(!m_private->publish(topic, msg))
        return false;
    m_private->addHistory(uid, topic, name, Direction::Out);
    emit recordsChanged();
    return true;
}

bool Mqtti::subscribe(const QString& topic_name) {
    QMqttTopicFilter topic(topic_name);
    if(!topic.isValid()) {
        emit error(QString("Invalid topic").arg(topic_name));
        qDebug() << topic_name << "invalid topic";
        return false;
    }

    if(!m_private->subscribe(topic)) {
        qDebug() << topic_name << "subscribe failed";
        return false;
    }

    emit subscriptionsChanged();
    return true;
}

bool Mqtti::unsubscribe(const QString& topic_name) {
     QMqttTopicFilter topic(topic_name);
    if(!topic.isValid()) {
        emit error(QString("Invalid topic").arg(topic_name));
        return false;
    }

    if(!m_private->unSubscribe(topic))
        return false;

    emit subscriptionsChanged();
    return true;
}


QStringList Mqtti::subscriptions() const {
    return m_private->subscriptions();
}
QUrl Mqtti::server() const {
    return m_private->server();
}

bool Mqtti::setServer(const QUrl& url) {
    if(!url.isValid())
        return false;
    if(m_private->server() != url) {
        if(!m_private->setServer(url))
            return false;
        emit serverChanged();
    }
    return true;
}

QString Mqtti::recordMessage(int index) const {
    return std::get<HISTORY_MESSAGE>(m_private->history(index));
}

QString Mqtti::recordTopic(int index) const {
    return std::get<HISTORY_TOPIC>(m_private->history(index));
}

bool Mqtti::recordOutwards(int index) const {
    return std::get<HISTORY_DIR>(m_private->history(index)) == Direction::Out;
}


int Mqtti::recordsSize() const {
    return m_private->historySize();
}


bool Mqtti::handleRawMessage(const QString& topic, const QByteArray& message) {
    emit rawReceived(topic, message);
    return true;
}

bool Mqtti::handleBinary(unsigned& pos, const QUuid& uuid, const QString& topic, const QByteArray& bytes) {
    const auto name_len = read<uint32_t>(pos, bytes);
    if(!name_len || *name_len > bytes.size() - pos) {
        emit error(ERR_TRUNCATED);
        return false;
    }
    const auto name = bytes.mid(pos, *name_len);
    pos += *name_len;
    const auto len = read<uint32_t>(pos, bytes);
    if(!len || *len > bytes.size() - pos) {
        emit error(ERR_TRUNCATED);
        return false;
    }
    auto data = bytes.mid(pos, *len);
    const auto index = m_private->storeBinary(QString(name), std::move(data));
    m_private->addHistory(uuid, topic, QString(name), Direction::In);
    emit binaryReceived(topic, index);
    emit recordsChanged();
    return true;
}

bool Mqtti::handleMessage(unsigned& pos, const QUuid& uuid, const QString& topic, const QByteArray& bytes) {
    const auto content_sz = read<uint32_t>(pos, bytes);
    if(!content_sz) {
        emit error(ERR_TRUNCATED);
        return false;
    }
    const QString content = bytes.mid(pos);
    if(content.size() != *content_sz) {
        emit error(ERR_CORRUPTED);
        return false;
    }
    m_private->addHistory(uuid, topic, content, Direction::In);
    emit messageReceived(topic, content);
    emit recordsChanged();
    return true;
}

bool Mqtti::handleMessage(unsigned& pos, const QString& topic, const QByteArray& message) {
    Q_ASSERT(pos == MAGIC_SIZE);
    const auto uuid = read<QUuid>(pos, message);
    if(!uuid) {
        emit error(ERR_TRUNCATED);
        return false;
    }
    if(!uuid->isNull() && m_private->contains(*uuid))
        return false;
    Q_ASSERT(pos == MAGIC_SIZE + UUID_SIZE);
    const auto kind = read<Kind>(pos, message);
    if(!kind) {
        emit error(ERR_TRUNCATED);
        return false;
    }
    Q_ASSERT(pos == MAGIC_SIZE + UUID_SIZE + 1);
    switch (*kind) {
    case Kind::Binary:
        if(!handleBinary(pos, *uuid, topic, message))
            return false;
        break;
    case Kind::Message:
        if(!handleMessage(pos, *uuid, topic, message))
            return false;
        break;
    default:
        qDebug() << "Bad kind" << *kind;
        emit error(ERR_CORRUPTED);
        return false;
    }
    return true;
}

QString Mqtti::binaryName(int index) const {
    return m_private->binary(index).first;
}

void Mqtti::deleteBinary(int index) {
    m_private->deleteBinary(index);
}

QByteArrayView Mqtti::binary(int index) const {
    return m_private->binary(index).second;
}

int Mqtti::binaryCount() const {
    return m_private->binaryCount();
}

bool Mqtti::setServer(const QString& serverName) {
    return setServer(QUrl::fromUserInput(serverName));
}
