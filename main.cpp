#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "openglrenderer.h"   // Votre classe OpenGLRenderer
#include "databasehandler.h" // Votre classe DatabaseHandler

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    // Enregistrer la classe OpenGLRenderer comme un type QML
    qmlRegisterType<OpenGLRenderer>("OpenGLRenderer", 1, 0, "OpenGLRenderer");

    // Enregistrer DatabaseHandler comme un singleton utilisable dans QML
    qmlRegisterSingletonType<DatabaseHandler>("DatabaseHandler", 1, 0, "DatabaseHandler",
        [](QQmlEngine *, QJSEngine *) -> QObject * {
            return new DatabaseHandler(); // Création d'une instance unique
 });

    QQmlApplicationEngine engine;
    // Ajouter le chemin vers le dossier contenant "qmldir"
    engine.addImportPath("qml");  // Ou le chemin relatif/absolu vers le dossier `OpenGLRenderer`

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
