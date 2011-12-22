#include "UnixDynaLib.hpp"
#include "IPlayer.h"


int main()
{
    UnixDynaLib  _lib;
    void *fct;
    IPlayer *monster;

    try{

    _lib.dynaLoad("./libtinymonster.so");
    fct = _lib.funcLoad("create");
    monster =
               ((monsterCall) (fct))(1,1,1,1,1);
    std::cout << monster->getSpeed() << std::endl;
    }
    catch (Exception *e)
    {
        std::cout << e->what() << std::endl;
    }
}
