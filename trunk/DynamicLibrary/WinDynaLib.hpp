#ifndef WINDYNALIB_HPP
#define WINDYNALIB_HPP

#include <windows.h>
#define DLL_IMPORT __declspec(dllimport)

typedef type (*f_NomFonction)(parametresFonction);
f_NomFonction p_NomFonction;


class WinDynaLib : public IDynaLib
{
public:
    WinDynaLib();

private:
    void        dynaLoad(String libName);
    void        *funcLoad(String funcName);
    void        dynaFree();
    HINSTANCE   _DLLHandle;
};

#endif // WINDYNALIB_HPP
