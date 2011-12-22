#include "WinDynaLib.hpp"

int main()
{
    WinDynaLib  _lib;

    _lib.dynaLoad("testTinyMonster.dll");
     _lib.funcLoad("create");
}
