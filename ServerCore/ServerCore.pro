CONFIG(SERVERCORE_MODULE) {
} else {

include(../Network/Network.pro)
include(../Protocol/Protocol.pro)
include(../ProtocolImplement/ProtocolImplement.pro)

INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/ServerGame.h \
    $$PWD/ServerCore.h \

SOURCES += \
    $$PWD/ServerGame.cpp \
    $$PWD/ServerCore.cpp \

win32: DEFINES += OS_WINDOWS
unix: DEFINES += OS_UNIX


 CONFIG += NETWORK_MODULE
 DEFINES += NETWORK_MODULE
}

HEADERS += \
    ServerCore/ServerMonster.h

SOURCES += \
    ServerCore/ServerMonster.cpp
