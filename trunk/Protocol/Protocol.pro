CONFIG(PROTOCOL_MODULE) {
} else {
INCLUDEPATH += $$PWD

include(../Network/Network.pro)

HEADERS += \
    $$PWD/Packet.h \
    $$PWD/LoginMapper.h \
    $$PWD/NetworkSlot.h \
    $$PWD/Protocol.h \
    $$PWD/PlayerInfo.h \
    $$PWD/TimerPool.h \


SOURCES += \
    $$PWD/Packet.cpp \
    $$PWD/LoginMapper.cpp \
    $$PWD/Protocol.cpp \
    $$PWD/PlayerInfo.cpp \
    #$$PWD/TimerPool.cpp




win32: DEFINES += OS_WINDOWS
unix: DEFINES += OS_UNIX

win32: LIBS += "$$PWD/../lib/libws2_32_win32.a"

 CONFIG += PROTOCOL_MODULE
 DEFINES += PROTOCOL_MODULE
}

