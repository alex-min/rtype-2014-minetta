CONFIG(MONSTER_MODULE) {
} else {
INCLUDEPATH += $$PWD

include(../Players/players.pro)
include(../Common/Common.pro)
include(../Players/Missile/MissileInclude.pro)
include(../DynamicLibrary/DynamicLibrary.pro)
include(../Players/TinyMonster/tinyMonsterInclude.pro)

HEADERS += \
    $$PWD/MonsterGenerator.h

SOURCES += \
    $$PWD/MonsterGenerator.cpp

 CONFIG += MONSTER_MODULE
 DEFINES += MONSTER_MODULE
}





