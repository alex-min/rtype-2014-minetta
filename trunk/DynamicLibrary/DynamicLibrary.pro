HEADERS += \
  $$PWD/ElfAutoLoad.cpp \
  $$PWD/ElfLoad.cpp

SOURCES += \
  $$PWD/ElfAutoLoad.h \
  $$PWD/ElfLoad.h           

win32: DEFINES += OS_WINDOWS
unix: DEFINES += OS_UNIX
