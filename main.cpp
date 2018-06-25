#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "sandpilemodel.h"
#include "spimageprovider.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<SandpileModel>("SandpileModel", 1, 0, "SandpileModel");
    SandpileModel sandPileModel;
    SpImageProvider *liveImageProvider(new SpImageProvider());

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("SandPileModel", &sandPileModel);
    engine.rootContext()->setContextProperty("liveImageProvider", liveImageProvider);
    engine.addImageProvider("live", liveImageProvider);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    QObject::connect(&sandPileModel, &SandpileModel::newImage, liveImageProvider, &SpImageProvider::updateImage);
//    QObject::connect(&sandPileModel, &SandpileModel::forceClose,&engine,[=]{engine.removeImageProvider("live");});

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
