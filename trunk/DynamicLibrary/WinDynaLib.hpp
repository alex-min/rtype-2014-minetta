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
    unsigned int	getWcharSize(const wchar_t *s);
    wchar_t             *convertStringToWchar(std::string const &s);
    std::string         convertWcharToString(const wchar_t *s);
    HINSTANCE   _DLLHandle;
};

#endif // WINDYNALIB_HPP
