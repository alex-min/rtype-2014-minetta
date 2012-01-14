#ifndef MONSTERGENERATOR_H
#define MONSTERGENERATOR_H
#include "IPlayer.h"
#include "Pool.h"
#include "myDynaLib.h"
#include "Missile.h"
#include "Singleton.h"
#include "ConfLoader.hpp"

namespace Generator
{
    typedef IPlayer* (*tinyFill)(UInt32,UInt32,UInt32,UInt32,UInt32);
    typedef IPlayer* (*tinyEmpty)();
    typedef IPlayer* (*missileEmpty)();
    typedef IPlayer* (*missileFull)(UInt32 screenWidth, UInt32 screenHeight,
                                    float x, float y, float a, float b);
}

class MonsterGenerator
{
    friend class Singleton<MonsterGenerator>;
public:
    enum e_Monster{
        UNKNOWN,
        MISSILE,
        TINYMONSTER
    };
    struct s_generator {
        e_Monster id;
        IPlayer    *(MonsterGenerator::*fct)();
        std::string imageName;
    };
    IPlayer * generate(e_Monster);
    std::string const &getImageOf(e_Monster id);

private:
    IPlayer * generateMissile();
    IPlayer * generateTinyMonster();
    MonsterGenerator();
    MyDynaLib _dynalib;
    static s_generator          _generatorTab[3];
    const ConfObject                  *_conf;
};

typedef Singleton<MonsterGenerator> SingleMonsterGenerator;

#endif // MONSTERGENERATOR_H
