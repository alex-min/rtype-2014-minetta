#include "WinDynaLib.hpp"

WinDynaLib::WinDynaLib()
{
}

void    WinDynaLib::dynaLoad(std::string libName)
{
    _DLLHandle = LoadLibrary((WCHAR*)libName.c_str());
}

void    *WinDynaLib::funcLoad(std::string funcName)
{
    if (_DLLHandle != NULL)
        return((void *)GetProcAddress(_DLLHandle, funcName.c_str()));
    return (0);
}

void    WinDynaLib::dynaFree()
{
    FreeLibrary(_DLLHandle);
}
