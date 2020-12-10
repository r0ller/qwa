QT += quick
#__ANDROID__ is NOT for native Android build but to build webassembly qml for the android webview
#TODO: determine automatically based on target
#DEFINES +=__ANDROID__
DEFINES +=__NODEJS__
#DEFINES +=__NATIVE__
#Uncomment for __NATIVE__ build:
#DEPENDPATH += . ../build-qwa_pure_backend-x86_bsd_netbsd_elf_64bit-Debug
#LIBS += -L../build-qwa_pure_backend-x86_bsd_netbsd_elf_64bit-Debug -lqwa_pure_backend
#INCLUDEPATH += /home/r0ller/qwa/qwa_pure_backend

CONFIG += c++11
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        messageboard.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    messageboard.h
