#include "UnixDynaLib.hpp"

UnixDynaLib::UnixDynaLib()
{
}

void    UnixDynaLib::dynaLoad(std::string libName)
{

    _handle = dlopen(libName.c_str(), RTLD_LAZY);

    if (_handle == NULL)
       throw new Exception(dlerror());
    dlerror();
}

void    *UnixDynaLib::funcLoad(std::string funcName)
{
    char *error;
    void *tmp = dlsym(_handle, funcName.c_str());

    if ((error = dlerror()) != NULL)  {
        throw new Exception(error);
    }
    return (tmp);
}

void    UnixDynaLib::dynaFree()
{
    if (_handle)
    {
        dlclose(_handle);
    }
}
