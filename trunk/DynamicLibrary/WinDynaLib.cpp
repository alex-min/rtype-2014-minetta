#include "WinDynaLib.hpp"

WinDynaLib::WinDynaLib()
{
}

void    WinDynaLib::dynaLoad(String libName)
{
    _DLLHandle = LoadLibrary(libName);
}

void    *WinDynaLib::funcLoad(String funcName)
{
    if (DLLHandle != NULL)
        return(p_NomFonction = (f_Encode)GetProcAddress(DLLHandle, funcName));
    return (0);
}

void    WinDynaLib::dynaFree()
{
    FreeLibrary(_DLLHandle);
}
