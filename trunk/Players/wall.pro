CONFIG(WALL_MODULE) {
} else {
INCLUDEPATH += $$PWD

include(../Collision/Collision.pro)
 
HEADERS += \
    $$PWD/Wall.h

SOURCES += \
    $$PWD/Wall.cpp

 CONFIG += WALL_MODULE
 DEFINES += WALL_MODULE
}

