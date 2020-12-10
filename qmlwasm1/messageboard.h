#ifndef MESSAGEBOARD_H
#define MESSAGEBOARD_H
#include <QObject>
#include <QDebug>
#if defined(__ANDROID__) || defined(__NODEJS__)
#include <emscripten.h>
#endif

class messageboard : public QObject
{
    Q_OBJECT
public:
    explicit messageboard(QObject *parent = nullptr);
    Q_INVOKABLE bool postMessage(const QString &msg);
    static void (*fptr_callbackMsg)(const char* msg);
    static void callbackMsg(const char* msg);
    static void setRootObject(QObject*);
    static QObject* getRootObject();

public slots:
    void refresh();

private:
    static QObject* rootObject;

signals:

};
#endif // MESSAGEBOARD_H
