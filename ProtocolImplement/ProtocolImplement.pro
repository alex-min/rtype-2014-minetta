CONFIG(PROTOCOLIMPLEMENT_MODULE) {
} else {
INCLUDEPATH += $$PWD

include(../Protocol/Protocol.pro)

win32: DEFINES += OS_WINDOWS
unix: DEFINES += OS_UNIX

HEADERS += \
    $$PWD/ConnectionSlot.h \
    $$PWD/ProtocolImplement.h \
    $$PWD/ServerData.h \
    $$PWD/MoveSlot.h \
    $$PWD/CreateGameSlot.h \
    $$PWD/ListGameSlot.h \
    $$PWD/JoinGameSlot.h \
    $$PWD/PongSlot.h \
    $$PWD/DeadSlot.h \
    $$PWD/EndGameSlot.h

SOURCES += \
    $$PWD/ConnectionSlot.cpp \
    $$PWD/ServerData.cpp \
    $$PWD/MoveSlot.cpp \
    $$PWD/CreateGameSlot.cpp \
    $$PWD/ListGameSlot.cpp \
    $$PWD/JoinGameSlot.cpp \
    $$PWD/PongSlot.cpp \
    $$PWD/DeadSlot.cpp \
    $$PWD/EndGameSlot.cpp


 CONFIG += PROTOCOLIMPLEMENT_MODULE
 DEFINES += PROTOCOLIMPLEMENT_MODULE
}

HEADERS += \
    $$PWD/PopSlot.h


SOURCES += \
    $$PWD/PopSlot.cpp
