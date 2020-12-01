#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#if !defined(__ANDROID__) && !defined(__EMSCRIPTEN__)
#include "receiver.h"
#endif
#if defined(__ANDROID__) || defined(__EMSCRIPTEN__)
#include <emscripten.h>
#endif
#include "messageboard.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    //TODO:instantiate messageboard with rootobject as parent?
    messageboard msgBoard;
    engine.rootContext()->setContextProperty("msgBoard", &msgBoard);
    engine.load(url);
    msgBoard.setRootObject(engine.rootObjects().first());
    #ifdef __ANDROID__
    EM_ASM({
        window.onmessage=function(e){
            window.msgPort=e.ports[0];
            //console.log('js:'+e.data);
            window.msgPort.onmessage=function(f){
                //let result=JSON.parse(f.data);
                //TODO: https://stackoverflow.com/questions/29319208/call-c-function-pointer-from-javascript
                dynCall('vi',$0,[allocate(intArrayFromString(f.data),'i8',ALLOC_NORMAL)]);
                //console.log('js:'+f.data);
            }
        }
    },messageboard::fptr_callbackMsg);
    #endif
    return app.exec();
}
