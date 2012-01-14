CONFIG(LIBC_MODULE) {
} else {
INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/Memset.h \
    $$PWD/LibC.h \
    $$PWD/Memcpy.h

SOURCES += \
    $$PWD/Memset.cpp \
    $$PWD/Memcpy.cpp

win32: DEFINES += OS_WINDOWS
unix: DEFINES += OS_UNIX

 CONFIG += LIBC_MODULE
 DEFINES += LIBC_MODULE
}

HEADERS += \

SOURCES += \

