#ifndef IDYNALIB_H_
#define IDYNALIB_H_

#include <iostream>
#include "Exception.h"

class IDynaLib
{
public:
    virtual ~IDynaLib() {}
    virtual void    dynaLoad(std::string libName) = 0;
    virtual void    *funcLoad(std::string funcName) = 0;
    virtual void    dynaFree() = 0;
};




#endif // IDYNALIB_H
