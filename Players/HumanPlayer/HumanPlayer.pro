CONFIG(HUMANPLAYER_MODULE) {
} else {
INCLUDEPATH += $$PWD

include(../players.pro)
include (../../SfmlCommon/SfmlCommon.pro)
include (../Missile/MissileInclude.pro)

HEADERS += $$PWD/HumanPlayer.h

SOURCES += $$PWD/HumanPlayer.cpp

 CONFIG += HUMANPLAYER_MODULE
 DEFINES += HUMANPLAYER_MODULE
}