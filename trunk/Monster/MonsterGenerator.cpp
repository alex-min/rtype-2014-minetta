#include "MonsterGenerator.h"

MonsterGenerator::s_generator MonsterGenerator::_generatorTab[] =
{
    {MonsterGenerator::MISSILE, &MonsterGenerator::generateMissile, "r-typesheet1.png"},
    {MonsterGenerator::TINYMONSTER, &MonsterGenerator::generateTinyMonster, "r-typesheet9.png"},
    {MonsterGenerator::UNKNOWN, 0, ""}
};

std::string const &MonsterGenerator::getImageOf(e_Monster id)
{
    for (int i = 0; _generatorTab[i].fct; i++)
        if (_generatorTab[i].id == id)
            return (_generatorTab[i].imageName);
}

MonsterGenerator::MonsterGenerator()
{
    _dynalib = MyDynaLib();
    _conf = ConfLoader::getInstance()->getConfObjectFor("./monster_conf");
}

IPlayer * MonsterGenerator::generateMissile()
{
    std::string path = _conf->getStringValueOf("missile_path");
    _dynalib.dynaLoad(path);
    Generator::missileEmpty fct = reinterpret_cast<Generator::missileEmpty>(_dynalib.funcLoad("create"));
    IPlayer *tmp = fct();

    return (tmp);
}

IPlayer * MonsterGenerator::generateTinyMonster()
{
    _dynalib.dynaLoad(_conf->getStringValueOf("tinymonster_path"));
    Generator::missileEmpty fct = reinterpret_cast<Generator::missileEmpty>(_dynalib.funcLoad("create"));
    IPlayer *tmp = fct();
    return (tmp);
}

IPlayer * MonsterGenerator::generate(e_Monster id)
{
    for (int i = 0; _generatorTab[i].fct; i++)
        if (_generatorTab[i].id == id)
            return (this->*(_generatorTab[i].fct))();
    return (0);
}

