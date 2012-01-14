CONFIG(COMMON_MODULE) {
} else {
INCLUDEPATH += $$PWD


HEADERS += \
    $$PWD/MyString.h \
    $$PWD/Point.h \
    $$PWD/Thread.h \
    $$PWD/Singleton.h \
    $$PWD/ScopedLock.h \
    $$PWD/PThreadThread.h \
    $$PWD/Pool.h \
    $$PWD/Mutex.h \
    $$PWD/CircularBuffer.h \
    $$PWD/IThread.h \
    $$PWD/IMutex.h \
    $$PWD/PThreadMutex.h \
    $$PWD/ConfLoader.hpp \
    $$PWD/Exception.h \
    $$PWD/BaseRegex.h \
    $$PWD/SystemDefines.h \
    $$PWD/Timer.h \
    $$PWD/ITime.h \
    $$PWD/TimerPool.h \
    $$PWD/MySleep.h \
    $$PWD/ConfObject.h \
    $$PWD/CRC.h


SOURCES += \
    $$PWD/MyString.cpp \
    $$PWD/ScopedLock.cpp \
    $$PWD/CircularBuffer.cpp \
    $$PWD/PThreadThread.cpp \
    $$PWD/PThreadMutex.cpp \
    $$PWD/ConfLoader.cpp \
    $$PWD/Exception.cpp \
    $$PWD/BaseRegex.cpp \
    $$PWD/Timer.cpp \
    $$PWD/ConfObject.cpp \
    $$PWD/CRC.cpp

unix {
SOURCES +=  $$PWD/UNIXTime.cpp
HEADERS +=  $$PWD/UNIXTime.h
}

win32 {
SOURCES +=  $$PWD/WindowsTime.cpp
HEADERS +=  $$PWD/WindowsTime.h
}

win32: DEFINES += OS_WINDOWS
unix: DEFINES += OS_UNIX

win32: LIBS += "$$PWD/../lib/libpthreadGC2_win32.a" \


DEFINES += COMMON_MODULE
CONFIG += COMMON_MODULE
}

HEADERS += \


SOURCES += \




