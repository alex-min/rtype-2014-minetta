CONFIG(TINYMONSTER_MODULE) {
} else {
INCLUDEPATH += $$PWD

include(../players.pro)
include(../../winLib/sfmllib.pro)
TEMPLATE = lib
CONFIG += dll

HEADERS += \
    TinyMonster.h

SOURCES += \
    TinyMonster.cpp

 CONFIG += TINYMONSTER_MODULE
 DEFINES += TINYMONSTER_MODULE
}

SOURCES += \
    main.cpp

