CONFIG(COLLISION_MODULE) {
} else {
INCLUDEPATH += $$PWD

include(../Common/Common.pro)

HEADERS += $$PWD/Object.h

win32: DEFINES += OS_WINDOWS
unix: DEFINES += OS_UNIX

win32: LIBS += "$$PWD/../lib/libpthreadGC2_win32.a"


DEFINES += COLLISION_MODULE
CONFIG += COLLISION_MODULE
}
