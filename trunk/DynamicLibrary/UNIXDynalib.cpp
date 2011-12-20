#include "UnixDynaLib.hpp"

UnixDynaLib::UnixDynaLib()
{
}

void    UnixDynaLib::dynaLoad(String libName)
{
    _elf.dumpFile(libName);
}

void    *UnixDynaLib::funcLoad(String funcName)
{
    const std::list<const ElfSymbol *> & symList = _elf.extractSymbolList();
    for (std::list<const ElfSymbol *>::const_iterator it = symList.begin();
         it != symList.end(); ++it)
        if (funcName == _elf.getSymbolName(*it))
            return(_elf.getSymbolName(*it));
    return (0);
}

void    UnixDynaLib::dynaFree()
{
    ;
}
