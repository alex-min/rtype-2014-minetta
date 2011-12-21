CONFIG(PROTOCOL_MODULE) {
} else {
INCLUDEPATH += $$PWD

include(../Network/Network.pro)

HEADERS += \



SOURCES += \

win32: DEFINES += OS_WINDOWS
unix: DEFINES += OS_UNIX

win32: LIBS += "$$PWD/../lib/libws2_32_win32.a"

 CONFIG += PROTOCOL_MODULE
 DEFINES += PROTOCOL_MODULE
}

HEADERS += \
    Protocol/Packet.h \
    Protocol/LoginMapper.h

SOURCES += \
    Protocol/Packet.cpp \
    Protocol/LoginMapper.cpp
