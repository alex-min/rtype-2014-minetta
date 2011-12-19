INCLUDEPATH +=


HEADERS += \
    $$PWD/String.h \
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
    $$PWD/BaseRegex.h

SOURCES += \
    $$PWD/String.cpp \
    $$PWD/ScopedLock.cpp \
    $$PWD/CircularBuffer.cpp \
    $$PWD/PThreadThread.cpp \
    $$PWD/PThreadMutex.cpp \
    $$PWD/ConfLoader.cpp \
    $$PWD/Exception.cpp \
    $$PWD/BaseRegex.cpp

win32: DEFINES += OS_WINDOWS
unix: DEFINES += OS_UNIX

DEFINES += COMMON_MODULE




