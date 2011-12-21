CONFIG(LIBC_MODULE) {
} else {
INCLUDEPATH += $$PWD

HEADERS += \
  $$PWD/Memset.h

SOURCES += \
  $$PWD/Memset.cpp

win32: DEFINES += OS_WINDOWS
unix: DEFINES += OS_UNIX

 CONFIG += LIBC_MODULE
 DEFINES += LIBC_MODULE
}

HEADERS += \
    $$PWD/LibC.h \
    LibCWrapper/Memcpy.h

SOURCES += \
    LibCWrapper/Memcpy.cpp
