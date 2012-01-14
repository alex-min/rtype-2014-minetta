CONFIG(TINYMONSTER_MODULE) {
} else {
INCLUDEPATH += $$PWD
QT       -= core gui
TARGET = tinymonster
DEFINES += TINYMONSTER_LIBRARY
include(../players.pro)
include(../Missile/MissileInclude.pro)

TEMPLATE = lib
CONFIG += dll

HEADERS += \
    $$PWD/TinyMonster.h

SOURCES += \
    $$PWD/TinyMonster.cpp

 CONFIG += TINYMONSTER_MODULE
 DEFINES += TINYMONSTER_MODULE
}
