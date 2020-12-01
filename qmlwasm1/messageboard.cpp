#include "messageboard.h"
#if !defined(__ANDROID__) && !defined(__EMSCRIPTEN__)
#include "receiver.h"
#endif

void (*messageboard::fptr_callbackMsg)(const char* msg)=NULL;
QObject* messageboard::rootObject;

messageboard::messageboard(QObject *parent) : QObject(parent)
{
    messageboard::fptr_callbackMsg=&messageboard::callbackMsg;
}

bool messageboard::postMessage(const QString &msg) {
    #ifndef __ANDROID__
        qDebug() << "Called the C++ method with" << msg;
        QObject* obj=messageboard::rootObject->findChild<QObject*>("mousearea");
        qDebug()<<obj->objectName();
        const char* response=execute(msg.toStdString().c_str());
        QMetaObject::invokeMethod(obj,"clickReturn",Q_ARG(QString, QString(response)));
        return true;
    #endif
    #ifdef __ANDROID__
        EM_ASM({
            window.msgPort.postMessage(UTF8ToString($0));
        },msg.toStdString().c_str());
    #endif
}

void messageboard::refresh() {
    #ifndef __ANDROID__
        qDebug() << "Called the C++ slot";
    #endif
    #ifdef __ANDROID__
        EM_ASM(
            console.log('Refresh');
        );
    #endif
}

void messageboard::callbackMsg(const char* msg){
    #ifdef __ANDROID__
        QObject* obj=messageboard::rootObject->findChild<QObject*>("mousearea");
        QMetaObject::invokeMethod(obj,"clickReturn",Q_ARG(QString, QString(msg)));
//        EM_ASM({
//            console.log(UTF8ToString($0));
//        },obj->objectName().toStdString().c_str());//msg);
    #endif
}

void messageboard::setRootObject(QObject* rootObject){
    messageboard::rootObject=rootObject;
}
