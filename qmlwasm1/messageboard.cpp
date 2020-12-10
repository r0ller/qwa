#include "messageboard.h"
#ifdef __NATIVE__
#include "receiver.h"
#endif

#ifdef __NODEJS__
    void onload(unsigned handle, void *userData, void *data, unsigned size){
        std::string response((char*)data,size);
        EM_ASM({
            console.log("onload:"+UTF8ToString($0));
        },response.c_str());
        QObject* obj=messageboard::getRootObject()->findChild<QObject*>("mousearea");
        QMetaObject::invokeMethod(obj,"clickReturn",Q_ARG(QString, QString(response.c_str())));
    }
    void onerror(unsigned handle, void *userData, int status, const char *message){
        EM_ASM({
            console.log("onerror");
        });
    }
    void onprogress(unsigned handle, void *userData, int loaded, int total){
        EM_ASM({
            console.log("onprogress");
        });
    }
#endif


void (*messageboard::fptr_callbackMsg)(const char* msg)=NULL;
QObject* messageboard::rootObject;

messageboard::messageboard(QObject *parent) : QObject(parent)
{
    messageboard::fptr_callbackMsg=&messageboard::callbackMsg;
}

bool messageboard::postMessage(const QString &msg) {
    #ifdef __NATIVE__
        qDebug() << "Called the C++ method with" << msg;
        QObject* obj=messageboard::rootObject->findChild<QObject*>("mousearea");
        qDebug()<<obj->objectName();
        const char* response=execute(msg.toStdString().c_str());
        QMetaObject::invokeMethod(obj,"clickReturn",Q_ARG(QString, QString(response)));
    #endif
    #ifdef __NODEJS__
        QString param="command="+msg;
        emscripten_async_wget2_data("/","POST",param.toStdString().c_str(),NULL,true,&onload,&onerror,&onprogress);
    #endif
    #ifdef __ANDROID__
        EM_ASM({
            //console.log("postMessage");
            window.msgPort.postMessage(UTF8ToString($0));
        },msg.toStdString().c_str());
    #endif
    return true;
}

void messageboard::refresh() {
    #if defined(__NATIVE__) || defined(__NODEJS__)
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

QObject* messageboard::getRootObject(){
    return messageboard::rootObject;
}
