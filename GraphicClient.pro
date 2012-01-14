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
include(./DynamicLibrary/DynamicLibrary.pro)
include(./Map/Map.pro)
include (./Monster/Monster.pro)

INCLUDEPATH += ./SfmlCommon/

QT       += core gui

TARGET = GraphicClient
TEMPLATE = app

SOURCES += $$PWD/GraphicClient/main.cpp\
    $$PWD/GraphicClient/QSFMLCanvas.cpp \
    $$PWD/GraphicClient/MyCanvas.cpp \
    $$PWD/GraphicClient/Game.cpp \
    $$PWD/GraphicClient/ListenServer.cpp \
    $$PWD/GraphicClient/MoveSlot.cpp \
    $$PWD/GraphicClient/ConnectedSlot.cpp \
    $$PWD/GraphicClient/LoginScreen.cpp \
    $$PWD/GraphicClient/GameManager.cpp \
    $$PWD/GraphicClient/GamesList.cpp \
    $$PWD/GraphicClient/ListGameSlot.cpp \
    $$PWD/GraphicClient/CreateGameScreen.cpp \
    $$PWD/GraphicClient/CreateGameSlot.cpp \
    $$PWD/GraphicClient/RefGameSlot.cpp \
    $$PWD/GraphicClient/MapScrolling.cpp \
    $$PWD/GraphicClient/Scrolling.cpp \
    $$PWD/GraphicClient/PopSlot.cpp \
    $$PWD/GraphicClient/MonsterItem.cpp \
    $$PWD/GraphicClient/WaitWidget.cpp \
    $$PWD/GraphicClient/StartGameSlot.cpp \
    $$PWD/GraphicClient/DieSlot.cpp \
    $$PWD/GraphicClient/Sounds.cpp

HEADERS  += $$PWD/GraphicClient/QSFMLCanvas.h \
    $$PWD/GraphicClient/MyCanvas.h \
    $$PWD/GraphicClient/Game.h \
    $$PWD/GraphicClient/ListenServer.h \
    $$PWD/GraphicClient/MoveSlot.h \
    $$PWD/GraphicClient/ConnectedSlot.h \
    $$PWD/GraphicClient/LoginScreen.h \
    $$PWD/GraphicClient/GameManager.h \
    $$PWD/GraphicClient/GamesList.h \
    $$PWD/GraphicClient/ListGameSlot.h \
    $$PWD/GraphicClient/CreateGameScreen.h \
    $$PWD/GraphicClient/CreateGameSlot.h \
    $$PWD/GraphicClient/RefGameSlot.h \
    $$PWD/GraphicClient/MapScrolling.h \
    $$PWD/GraphicClient/Scrolling.h \
    $$PWD/GraphicClient/PopSlot.h \
    $$PWD/GraphicClient/MonsterItem.h \
    $$PWD/GraphicClient/WaitWidget.h \
    $$PWD/GraphicClient/StartGameSlot.h \
    $$PWD/GraphicClient/DieSlot.h \
    $$PWD/GraphicClient/ISounds.h \
    $$PWD/GraphicClient/Sounds.h

unix: LIBS += -lm

 CONFIG += GRAPHICCLIENT_MODULE
 DEFINES += GRAPHICCLIENT_MODULE
}
