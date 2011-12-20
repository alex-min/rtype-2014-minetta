#ifndef IDYNALIB_H_
#define IDYNALIB_H_

class IDynaLib
{
public:
    IDynaLib();
protected:
    void    dynaLoad(String libName) = 0;
    void    *funLoad(String funcName) = 0;
    void    dynaFree() = 0;
};




#endif // IDYNALIB_H
