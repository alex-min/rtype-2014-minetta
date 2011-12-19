CONFIG(NETWORK_MODULE) {
} else {
INCLUDEPATH += $$PWD

include(../Common/Common.pro)
include(../LibCWrapper/LibC.pro)

HEADERS += \
  $$PWD/IpAddress.h

SOURCES += \
  $$PWD/IpAddress.cpp

win32: DEFINES += OS_WINDOWS
unix: DEFINES += OS_UNIX

 CONFIG += NETWORK_MODULE
 DEFINES += NETWORK_MODULE
}
