HEADERS += \
    String.h \
    Point.h \
    Thread.h \
    Singleton.h \
    ScopedLock.h \
    PThreadThread.h \
    Pool.h \
    Mutex.h \
    CircularBuffer.h \
    IThread.h \
    IMutex.h \
    PThreadMutex.h

SOURCES += \
    String.cpp \
    ScopedLock.cpp \
    CircularBuffer.cpp \
    PThreadThread.cpp \
    PThreadMutex.cpp

win32: DEFINES += OS_WINDOWS
unix: DEFINES += OS_UNIX
