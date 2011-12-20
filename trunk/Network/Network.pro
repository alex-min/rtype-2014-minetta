CONFIG(NETWORK_MODULE) {
} else {
INCLUDEPATH += $$PWD

include(../Common/Common.pro)
include(../LibCWrapper/LibC.pro)

HEADERS += \
  $$PWD/ISocket.h \
  $$PWD/MySocket.h \
  $$PWD/IpAddress.h \
  $$PWD/NetworkDisconnect.h


SOURCES += \
  $$PWD/IpAddress.cpp

win32: DEFINES += OS_WINDOWS
unix: DEFINES += OS_UNIX

win32: LIBS += "$$PWD/../lib/libws2_32_win32.a"

unix {
    HEADERS += \
    $$PWD/UNIXSocket.h

    SOURCES += \
    $$PWD/UNIXSocket.cpp
}

win32 {
    HEADERS += \
    $$PWD/WindowsSocket.h

SOURCES += \
    $$PWD/WindowsSocket.cpp
}

 CONFIG += NETWORK_MODULE
 DEFINES += NETWORK_MODULE
}







