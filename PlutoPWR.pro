QT += core gui
QT += widgets
QT += charts

CONFIG += c++17 console
CONFIG -= app_bundle

SOURCES += \
        PlutoDevice.cpp \
        main.cpp
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    PlutoDevice.h

LIBS += -liio
