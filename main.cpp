#include "firebasehandler.h"
#include "qjsonobject.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QJsonDocument>
#include <QLocale>
#include <QTranslator>

#include <RestAPI/restclient.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    FireBaseHandler client;
    client.setAPIKey("AIzaSyCFGkEvj8zkfm0BQTTfG1OOgU2lFOYPIWU");
    client.signUserIn("lol@hotmail.com", "123456");








    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Rpg_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/Rpg/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
