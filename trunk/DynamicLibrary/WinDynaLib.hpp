#ifndef WINDYNALIB_HPP
#define WINDYNALIB_HPP

#include <windows.h>
#include "IDynaLib.hpp"
#define DLL_IMPORT __declspec(dllimport)

class WinDynaLib : public IDynaLib
{
public:
    WinDynaLib();
    virtual void        dynaLoad(std::string libName);
    virtual void        *funcLoad(std::string funcName);
    virtual void        dynaFree();
    HINSTANCE   _DLLHandle;
};

#endif // WINDYNALIB_HPP
