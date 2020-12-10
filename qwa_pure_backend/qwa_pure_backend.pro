TEMPLATE = lib
CONFIG += c++11
CONFIG -= qt
#uncomment for __NODEJS__ build
#CONFIG+= -o libqwa_pure_backend.js -s EXPORTED_FUNCTIONS="['_execute']" -s EXTRA_EXPORTED_RUNTIME_METHODS="['ccall']"
SOURCES += \
    receiver.cpp

HEADERS += \
    receiver.h
