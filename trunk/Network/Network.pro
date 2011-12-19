HEADERS += \
  $$PWD/IpAddress.h

SOURCES += \
  $$PWD/IpAddress.cpp

win32: DEFINES += OS_WINDOWS
unix: DEFINES += OS_UNIX
