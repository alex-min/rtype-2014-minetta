#include "WinDynaLib.hpp"

int main()
{
    WinDynaLib  _lib;

    _lib.dynaLoad("aaclient.dll");
    _lib.funcLoad("LoadClientAdapter");
}
