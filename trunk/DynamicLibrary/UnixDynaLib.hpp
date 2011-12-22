#ifndef UNIXDYNALIB_HPP
#define UNIXDYNALIB_HPP

#include <dlfcn.h>
#include "IDynaLib.hpp"

class UnixDynaLib : public IDynaLib
{
public:
    UnixDynaLib();
    virtual void    dynaLoad(std::string libName);
    virtual void    *funcLoad(std::string funcName);
    virtual void    dynaFree();
private:
    void *_handle;
};

#endif // UNIXDYNALIB_HPP
