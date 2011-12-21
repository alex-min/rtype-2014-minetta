#-------------------------------------------------
#
# Project created by QtCreator 2011-12-19T15:32:08
#
#-------------------------------------------------

include(./GraphicClient/SfmlCommon/SfmlCommon.pro)

INCLUDEPATH += ./GraphicClient/SfmlCommon/

QT       += core gui

TARGET = GraphicClient
TEMPLATE = app

SOURCES += ./GraphicClient/main.cpp\
    ./GraphicClient/QSFMLCanvas.cpp \
    ./GraphicClient/MyCanvas.cpp \
    ./GraphicClient/Game.cpp \
    ./Common/PThreadMutex.cpp \
    ./Common/PThreadThread.cpp \
    ./Common/ScopedLock.cpp

HEADERS  += ./GraphicClient/QSFMLCanvas.h \
    ./GraphicClient/MyCanvas.h \
    ./GraphicClient/Game.h \
    ./Common/Singleton.h \
    ./Common/Thread.h \
    ./Common/Mutex.h \
    ./Common/ScopedLock.h












