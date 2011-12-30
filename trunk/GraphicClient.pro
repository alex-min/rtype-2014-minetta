#-------------------------------------------------
#
# Project created by QtCreator 2011-12-19T15:32:08
#
#-------------------------------------------------

CONFIG(GRAPHICCLIENT_MODULE) {
} else {
INCLUDEPATH += $$PWD

include(./Players/HumanPlayer/HumanPlayer.pro)
include(./AbstractThread/AQThread.pro)
include(./Network/Network.pro)
include(./Protocol/Protocol.pro)

INCLUDEPATH += ./SfmlCommon/

QT       += core gui

TARGET = GraphicClient
TEMPLATE = app

SOURCES += $$PWD/GraphicClient/main.cpp\
    $$PWD/GraphicClient/QSFMLCanvas.cpp \
    $$PWD/GraphicClient/MyCanvas.cpp \
    $$PWD/GraphicClient/Game.cpp \
    $$PWD/GraphicClient/ListenServer.cpp

HEADERS  += $$PWD/GraphicClient/QSFMLCanvas.h \
    $$PWD/GraphicClient/MyCanvas.h \
    $$PWD/GraphicClient/Game.h \
    $$PWD/GraphicClient/ListenServer.h

 CONFIG += GRAPHICCLIENT_MODULE
 DEFINES += GRAPHICCLIENT_MODULE
}










