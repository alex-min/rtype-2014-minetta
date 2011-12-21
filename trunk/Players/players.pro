CONFIG(PLAYERS_MODULE) {
} else {
INCLUDEPATH += $$PWD

include(../Common/Common.pro)
include(../GraphicClient/SfmlCommon/SfmlCommon.pro)

HEADERS += \
    $$PWD/APlayer.h \
    $$PWD/IPlayer.h

SOURCES += \
    $$PWD/APlayer.cpp

 CONFIG += PLAYERS_MODULE
 DEFINES += PLAYERS_MODULE
}
