CONFIG += ordered
include(Common/Common.pro)
include(Players/players.pro)
include(ServerCore/ServerCore.pro)


HEADERS += \
  

SOURCES += \
  ./Server/Main.cpp

win32: DEFINES += OS_WINDOWS
unix: DEFINES += OS_UNIX

