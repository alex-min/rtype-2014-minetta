CONFIG(PROTOCOLIMPLEMENT_MODULE) {
} else {
INCLUDEPATH += $$PWD

include(../Protocol/Protocol.pro)

win32: DEFINES += OS_WINDOWS
unix: DEFINES += OS_UNIX

HEADERS += \
    $$PWD/ConnectionSlot.h \
    $$PWD/ProtocolImplement.h \
    $$PWD/ServerData.h


SOURCES += \
    $$PWD/ConnectionSlot.cpp \
    $$PWD/ServerData.cpp


 CONFIG += PROTOCOLIMPLEMENT_MODULE
 DEFINES += PROTOCOLIMPLEMENT_MODULE
}

