#ifndef UNIXDYNALIB_HPP
#define UNIXDYNALIB_HPP
#ifdef OS_UNIX

#include <dlfcn.h>
#include "IDynaLib.hpp"
#define EXT ".so"
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

#endif
#endif // UNIXDYNALIB_HPP
