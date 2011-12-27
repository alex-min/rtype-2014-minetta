CONFIG(MISSILE_MODULE) {
} else {
INCLUDEPATH += $$PWD
QT       -= core gui
TARGET = missile
DEFINES += MISSILE_LIBRARY
include(../players.pro)
TEMPLATE = lib
CONFIG += dll

HEADERS += \
    $$PWD\Missile.h \
    $$PWD\Missile_global.h

SOURCES += \
    $$PWD\Missile.cpp

 CONFIG += MISSILE_MODULE
 DEFINES += MISSILE_MODULE
}
