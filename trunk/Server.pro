CONFIG += ordered
include(Common/Common.pro)
include(Network/Network.pro)


HEADERS += \
  

SOURCES += \
  ./Server/Main.cpp

win32: DEFINES += OS_WINDOWS
unix: DEFINES += OS_UNIX

