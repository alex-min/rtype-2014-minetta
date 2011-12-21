#-------------------------------------------------
#
# Project created by QtCreator 2011-12-19T15:32:08
#
#-------------------------------------------------

QT       += core gui

TARGET = GraphicClient
TEMPLATE = app


unix:LIBS += -lsfml-graphics -lsfml-window -lsfml-system -L/usr/X11R6/lib -lX11 -lpthread

SOURCES += ./GraphicClient/main.cpp\
    ./GraphicClient/QSFMLCanvas.cpp \
    ./GraphicClient/MyCanvas.cpp \
    ./GraphicClient/Game.cpp \
    ./GraphicClient/Image.cpp \
    ./GraphicClient/AnimatedImage.cpp \
    ./Common/PThreadMutex.cpp \
    ./Common/PThreadThread.cpp \
    ./Common/ScopedLock.cpp

HEADERS  += ./GraphicClient/QSFMLCanvas.h \
    ./GraphicClient/MyCanvas.h \
    ./GraphicClient/Game.h \
    ./GraphicClient/Image.h \
    ./GraphicClient/AnimatedImage.h \
    ./Common/Singleton.h \
    ./Common/Thread.h \
    ./Common/Mutex.h \
    ./Common/ScopedLock.h












