#pragma once

#include <QObject>
#include <QUrl>
#include <QQmlEngine>
#include <memory>


/**
 * @brief The Mqtti class
 *
 * publsh and subscribe MQTT
 *
 * Use publishMessage, messageReceived and binaryReceived for Mqtti - Mqtti messaging
 *
 * Use publishRaw and rawReceived for general MQTT
 *
 * Note: if you subscribe the same topic than you publish with raw you also receive the data.
 *
 * mqtti messaging history is stored ( in a limited ) history
 *
 */
class Mqtti : public QObject {
    Q_OBJECT
    Q_PROPERTY(QStringList subscriptions READ subscriptions NOTIFY subscriptionsChanged FINAL)
    Q_PROPERTY(QUrl server READ server WRITE setServer NOTIFY serverChanged FINAL)
public:
    explicit Mqtti(QObject *parent = nullptr);
    ~Mqtti();
    /// publish a message, uses internal header
    Q_INVOKABLE bool publishMessage(const QString& topic, const QString& msg);
    /// publish a message with binary data, uses internal header
    Q_INVOKABLE bool publishBinary(const QString& topic, const QString& msg, const QByteArray& bytes);
    /// publish plain bytes
    Q_INVOKABLE bool publishRaw(const QString& topic, const QByteArray& msg);
    /// subsribes a topic
    Q_INVOKABLE bool subscribe(const QString& topic);
    /// unsubscribes a topic
    Q_INVOKABLE bool unsubscribe(const QString& topic);
    /// return a recorded messages
    Q_INVOKABLE QString recordMessage(int index) const;
    Q_INVOKABLE QString recordTopic(int index) const;
    Q_INVOKABLE bool recordOutwards(int index) const;
    Q_INVOKABLE int recordsSize() const;
    Q_INVOKABLE int binaryCount() const;
    Q_INVOKABLE QString binaryName(int index) const;
    Q_INVOKABLE void deleteBinary(int index);
    QByteArrayView binary(int index) const;
    /// currently set server, regardless connected or not
    QUrl server() const;
    /// set server, return false if server url is not valid regardless if its changed
    bool setServer(const QString& serverName);
    /// set server, return false if server url is not valid regardless if its changed
    bool setServer(const QUrl& serverName);
    /// get list of current subscriptions
    QStringList subscriptions() const;
signals:
    void topicChanged();
    void subscriptionsChanged();
    void recordsChanged();
    void serverChanged();
    void error(const QString& errorMsg);
    void messageReceived(const QString& tpc, const QString& msg);
    void rawReceived(const QString& tpc, const QByteArray& data);
    void binaryReceived(const QString& tpc, int index);
private:
    bool handleRawMessage(const QString& topic, const QByteArray& message);
    bool handleMessage(unsigned& pos, const QString& topic, const QByteArray& message);
    bool handleBinary(unsigned& pos, const QUuid& uuid, const QString& topic, const QByteArray& message);
    bool handleMessage(unsigned& pos, const QUuid& uuid, const QString& topic, const QByteArray& message);
private:
    class Private;
    std::shared_ptr<Private> m_private;
};
