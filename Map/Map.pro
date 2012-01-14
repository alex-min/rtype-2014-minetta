CONFIG(MAP_MODULE) {
} else {
include (../Common/Common.pro)
INCLUDEPATH += $$PWD

QT -= core gui

SOURCES += \
    $$PWD/MapLoader.cpp \
    #main.cpp \

HEADERS += \
    $$PWD/MapLoader.h \



win32: DEFINES += OS_WINDOWS
unix: DEFINES += OS_UNIX

win32: LIBS += "$$PWD/../lib/libpthreadGC2_win32.a" \


DEFINES += MAP_MODULE
CONFIG += MAP_MODULE
}







