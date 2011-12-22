CONFIG(NETWORK_MODULE) {
} else {
INCLUDEPATH += $$PWD

include(../Common/Common.pro)
include(../LibCWrapper/LibC.pro)

HEADERS += \
  $$PWD/ISocket.h \
  $$PWD/MySocket.h \
  $$PWD/IpAddress.h \
  $$PWD/NetworkDisconnect.h \
  $$PWD/INetworkManager.h \
  $$PWD/MyNetworkManager.h \
  $$PWD/Network.h \
  $$PWD/NetworkManagerException.h \
  $$PWD/NetworkManagerSlot.h



SOURCES += \
  $$PWD/IpAddress.cpp \
  $$PWD/Network.cpp

win32: DEFINES += OS_WINDOWS
unix: DEFINES += OS_UNIX

win32: LIBS += "$$PWD/../lib/libws2_32_win32.a"

unix {
    HEADERS += \
    $$PWD/UNIXSocket.h \
    $$PWD/UNIXNetworkManager.h

    SOURCES += \
    $$PWD/UNIXSocket.cpp \
    $$PWD/UNIXNetworkManager.cpp

}

win32 {
    HEADERS += \
    $$PWD/WindowsSocket.h \
    $$PWD/WindowsNetworkManager.h


SOURCES += \
    $$PWD/WindowsSocket.cpp \
    $$PWD/WindowsNetworkManager.cpp

}

 CONFIG += NETWORK_MODULE
 DEFINES += NETWORK_MODULE
}



