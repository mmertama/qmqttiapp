#include <QtGui>
#include <QtQml>
#include "FigmaQmlInterface.hpp"
#include <mqtti.h>

int main(int argc, char** argv) {
    QGuiApplication app(argc, argv);
    app.setOrganizationName("FigmaQML");
    app.setOrganizationDomain("FigmaQML.com");
    app.setApplicationName("QMQtti");
    // for FigmaQml
    QQmlApplicationEngine engine;
    FigmaQmlInterface::registerFigmaQmlSingleton(engine);
    Mqtti mqtti;
    qmlRegisterSingletonInstance("MQTTI", 1, 0, "Mqtti", &mqtti);
    // for FigmaQml
    engine.addImportPath(":/");
    engine.load("qrc:/qml/main.qml");
    return app.exec();
}
