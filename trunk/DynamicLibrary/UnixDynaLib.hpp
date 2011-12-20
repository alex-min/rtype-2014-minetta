#ifndef UNIXDYNALIB_HPP
#define UNIXDYNALIB_HPP

class UnixDynaLib : public IDynaLib
{
public:
    UnixDynaLib();

private:
    void    dynaLoad(String libName);
    void    *funcLoad(String funcName);
    void    dynaFree();
    Elf32Load	_elf;
};

#endif // UNIXDYNALIB_HPP
