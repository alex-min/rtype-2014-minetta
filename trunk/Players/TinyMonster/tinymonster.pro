CONFIG(TINYMONSTER_MODULE) {
} else {
INCLUDEPATH += $$PWD
QT       -= core gui
TARGET = tinymonster
DEFINES += TINYMONSTER_LIBRARY
include(../players.pro)
TEMPLATE = lib
CONFIG += dll

HEADERS += \
    TinyMonster.h

SOURCES += \
    TinyMonster.cpp

 CONFIG += TINYMONSTER_MODULE
 DEFINES += TINYMONSTER_MODULE
}

SOURCES +=


