#include <QTest>
#include <QEventLoop>
#include <QTimer>
#include <vector>
#include "mqtti.h"



constexpr auto TOPIC_MSG = "MQTTI_TEST_TOPIC_MSG";
constexpr auto NOTHING = "NOTHING";
constexpr auto TEST_SERVER = "test.mosquitto.org";

template<typename T>
std::vector<T> fibonacci(T at) {
    if(at == 0) return {0};
    if(at == 1) return {0, 1};
    std::vector<T> fib(at);
    fib[0] = 0;
    fib[1] = 1;
    for (T i = 2; i < at; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    return fib;
}

static QByteArray mumble() {
    QByteArray bytes;
    for(const auto& f : fibonacci<quint32>(45)) {
        bytes.append(static_cast<char>(f));
        bytes.append(static_cast<char>(f >> 8));
        bytes.append(static_cast<char>(f >> 16));
        bytes.append(static_cast<char>(f >> 24));
    }
    return bytes;
}


class QMqttiTest: public QObject {
    Q_OBJECT
public:

private slots:

    void initTestCase() {
        qputenv("QTEST_FUNCTION_TIMEOUT", "100000");
        mqtti1 = new Mqtti(this);
        mqtti2 = new Mqtti(this);
        QObject::connect(mqtti1, &Mqtti::messageReceived, this, [this](const auto& topic, const auto& msg) {
            QCOMPARE(topic, TOPIC_MSG);
            expected_msg1 = msg;
        });
        QObject::connect(mqtti2, &Mqtti::messageReceived, this, [this](const auto& topic, const auto& msg) {
            QCOMPARE(topic, TOPIC_MSG);
            expected_msg2 = msg;
        });

        QObject::connect(mqtti1, &Mqtti::binaryReceived, this, [this](const auto& topic, const auto& index) {
            QCOMPARE(topic, TOPIC_MSG);
            expected_bin1 = mqtti1->binaryName(index);
        });
        QObject::connect(mqtti2, &Mqtti::binaryReceived, this, [this](const auto& topic, const auto& index) {
            QCOMPARE(topic, TOPIC_MSG);
            expected_bin2 = mqtti2->binaryName(index);
        });

    }

    void init() {
        expected_msg1 = NOTHING;
        expected_msg2 = NOTHING;
        expected_bin1 = NOTHING;
        expected_bin2 = NOTHING;
    }

    void serverSetTest() {
        QVERIFY(mqtti1->server().host().isEmpty());
        QCOMPARE(mqtti1->server().port(), 0);
        QVERIFY(mqtti1->setServer(TEST_SERVER));
        QCOMPARE(mqtti1->server().host(), TEST_SERVER);
        QCOMPARE(mqtti1->server().port(), 1883);
        QUrl uri;
        uri.setHost(TEST_SERVER);
        uri.setPort(1234);
        mqtti2->setServer(uri);
        QCOMPARE(mqtti2->server().host(), TEST_SERVER);
        QCOMPARE(mqtti2->server().port(), 1234);
        uri.setPort(1883);
        QVERIFY(mqtti2->setServer(uri));
        QCOMPARE(mqtti2->server().port(), 1883);
    }

    void subscribeTest() {
        QVERIFY(mqtti1->subscribe(TOPIC_MSG));
        QVERIFY(mqtti2->subscribe(TOPIC_MSG));
        QCOMPARE(mqtti1->subscriptions().size(), 1);
        QCOMPARE(mqtti1->subscriptions().front(), TOPIC_MSG);
    }

    void publishMsgTest() {
        QEventLoop loop;
        QObject::connect(mqtti2, &Mqtti::messageReceived,&loop, [&loop](auto, auto){loop.quit();});
        QObject::connect(mqtti1, &Mqtti::messageReceived,&loop, [&loop](auto, auto){loop.quit();});
        QObject::connect(mqtti2, &Mqtti::rawReceived, &loop, [](auto, auto){QFAIL("oops");});
        QObject::connect(mqtti1, &Mqtti::rawReceived, &loop, [](auto, auto){QFAIL("oops");});
        QObject::connect(mqtti2, &Mqtti::binaryReceived, &loop, [](auto, auto){QFAIL("oops");});
        QObject::connect(mqtti1, &Mqtti::binaryReceived, &loop, [](auto, auto){QFAIL("oops");});
        QCOMPARE(mqtti2->subscriptions().size(), 1);
        QCOMPARE(mqtti2->subscriptions().front(), TOPIC_MSG);
        QVERIFY(mqtti1->publishMessage(TOPIC_MSG, "foobar!"));
        loop.exec();
        // wait a bit if something should happen
        QTimer::singleShot(1000, &loop, [&loop](){loop.quit();});
        loop.exec();
        QCOMPARE(expected_msg1, NOTHING);
        QCOMPARE(expected_msg2, "foobar!");
        QCOMPARE(expected_bin1, NOTHING);
        QCOMPARE(expected_bin2, NOTHING);
    }

    void publishBinTest() {
        QEventLoop loop;
        QObject::connect(mqtti2, &Mqtti::binaryReceived,&loop, [&loop](auto, auto){loop.quit();});
        QObject::connect(mqtti1, &Mqtti::binaryReceived,&loop, [&loop](auto, auto){loop.quit();});
        QObject::connect(mqtti2, &Mqtti::rawReceived, &loop, [](auto, auto){QFAIL("oops");});
        QObject::connect(mqtti1, &Mqtti::rawReceived, &loop, [](auto, auto){QFAIL("oops");});
        QObject::connect(mqtti2, &Mqtti::messageReceived, &loop, [](auto, auto){QFAIL("oops");});
        QObject::connect(mqtti1, &Mqtti::messageReceived, &loop, [](auto, auto){QFAIL("oops");});
        QVERIFY(mqtti2->publishBinary(TOPIC_MSG, "barfoo!", mumble()));
        loop.exec();
        // wait a bit if something should happen
        QTimer::singleShot(1000, &loop, [&loop](){loop.quit();});
        loop.exec();
        QCOMPARE(expected_msg2, NOTHING);
        QCOMPARE(expected_msg1, NOTHING);
        QCOMPARE(expected_bin2, NOTHING);
        QCOMPARE(expected_bin1, "barfoo!");
        QCOMPARE(mqtti2->binaryCount(), 0);
        QCOMPARE(mqtti1->binaryCount(), 1);
        QCOMPARE(mqtti1->binaryName(0), "barfoo!");
        QCOMPARE(mqtti1->binary(0), mumble());
        mqtti1->deleteBinary(0);
        QCOMPARE(mqtti1->binaryCount(), 0);
    }

    void publishRawTest() {
        QEventLoop loop;
        auto count = 0;
        QObject::connect(mqtti2, &Mqtti::rawReceived, &loop, [&loop, &count](auto, auto){++count; loop.quit();});
        QObject::connect(mqtti1, &Mqtti::rawReceived, &loop, [&loop, &count](auto, auto){++count; loop.quit();});
        QObject::connect(mqtti2, &Mqtti::messageReceived, &loop, [&loop, &count](auto, auto){++count; loop.quit();});
        QObject::connect(mqtti1, &Mqtti::messageReceived, &loop, [&loop, &count](auto, auto){++count; loop.quit();});
        QObject::connect(mqtti2, &Mqtti::binaryReceived, &loop, [&loop, &count](auto, auto){++count; loop.quit();});
        QObject::connect(mqtti1, &Mqtti::binaryReceived, &loop, [&loop, &count](auto, auto){++count; loop.quit();});
        QVERIFY(mqtti1->publishRaw(TOPIC_MSG, "whatever!"));
        loop.exec();
        // wait a bit if something should happen
        QTimer::singleShot(1000, &loop, [&loop](){loop.quit();});
        loop.exec();
        QCOMPARE(expected_msg1, NOTHING);
        QCOMPARE(expected_msg2, NOTHING);
        QCOMPARE(expected_bin1, NOTHING);
        QCOMPARE(expected_bin2, NOTHING);
        QCOMPARE(count, 2); // ! also receiver gets - but no messages (or binary)
    }

    void unsubcribeTest() {
        QVERIFY(mqtti1->unsubscribe(TOPIC_MSG));
        QVERIFY(mqtti2->unsubscribe(TOPIC_MSG));
        QCOMPARE(mqtti1->subscriptions().size(), 0);
        expected_msg1 = NOTHING;
        expected_msg2 = NOTHING;
        QVERIFY(mqtti1->publishMessage(TOPIC_MSG, "foobarfoo!"));
        QVERIFY(mqtti2->publishMessage(TOPIC_MSG, "foobarbar!"));
        QEventLoop loop;
        QTimer::singleShot(1000, &loop, [&loop](){loop.quit();});
        loop.exec();
        QCOMPARE(expected_msg1, NOTHING);
        QCOMPARE(expected_msg2, NOTHING);
    }


    void recordsTest() {
        QCOMPARE(mqtti1->recordsSize(), 3); // both publish + subscribe + publish
        QCOMPARE(mqtti2->recordsSize(), 3);

        QCOMPARE(mqtti1->recordMessage(0), "foobar!");
        QCOMPARE(mqtti1->recordMessage(1), "barfoo!");
        QCOMPARE(mqtti1->recordMessage(2), "foobarfoo!");
        QCOMPARE(mqtti1->recordTopic(0), TOPIC_MSG);
        QCOMPARE(mqtti1->recordTopic(1), TOPIC_MSG);
        QCOMPARE(mqtti1->recordTopic(2), TOPIC_MSG);
        QCOMPARE(mqtti1->recordOutwards(0), true);
        QCOMPARE(mqtti1->recordOutwards(1), false);
        QCOMPARE(mqtti1->recordOutwards(2), true);

        QCOMPARE(mqtti2->recordMessage(0), "foobar!");
        QCOMPARE(mqtti2->recordMessage(1), "barfoo!");
        QCOMPARE(mqtti2->recordMessage(2), "foobarbar!");
        QCOMPARE(mqtti2->recordTopic(0), TOPIC_MSG);
        QCOMPARE(mqtti2->recordTopic(1), TOPIC_MSG);
        QCOMPARE(mqtti2->recordTopic(2), TOPIC_MSG);
        QCOMPARE(mqtti2->recordOutwards(0), false);
        QCOMPARE(mqtti2->recordOutwards(1), true);
        QCOMPARE(mqtti2->recordOutwards(2), true);
    }

    void cleanupTestCase() {
        delete mqtti1;
        delete mqtti2;
    }

private:
    Mqtti* mqtti1;
    Mqtti* mqtti2;
    QString expected_msg1;
    QString expected_msg2;
    QString expected_bin1;
    QString expected_bin2;
};
