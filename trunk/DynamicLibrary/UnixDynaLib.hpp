#ifndef UNIXDYNALIB_HPP
#define UNIXDYNALIB_HPP

#include "IDynaLib.hpp"

class UnixDynaLib : public IDynaLib
{
public:
    UnixDynaLib();
    virtual void    dynaLoad(std::string libName);
    virtual void    *funcLoad(std::string funcName);
    virtual void    dynaFree();
    Elf32Load	_elf;
};

#endif // UNIXDYNALIB_HPP
