HEADERS += \
  IpAddress.h

SOURCES += \
  IpAddress.cpp

win32: DEFINES += OS_WINDOWS
unix: DEFINES += OS_UNIX
