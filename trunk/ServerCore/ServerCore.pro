CONFIG(SERVERCORE_MODULE) {
} else {
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
