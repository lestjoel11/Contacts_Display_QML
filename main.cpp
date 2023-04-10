
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <contactitems.h>
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<ContactItems>("ContactItems", 1, 0, "ContactItems");
    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/ContactsDisplay/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
