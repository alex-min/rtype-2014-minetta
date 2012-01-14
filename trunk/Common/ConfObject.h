#ifndef CONFOBJECT_H
#define CONFOBJECT_H

#include <iostream>
#include <map>
#include "Exception.h"
#include "SystemDefines.h"

class ConfObject
{
public:
    ConfObject(std::string const &addr);
    void putLineInDico(std::string const &str);
    std::string const &getStringValueOf(std::string const &key) const;
    UInt16        getSize() const;
    const std::string & at(UInt16) const;

private:
    std::string _file;
    std::map<std::string, std::string> _dico;
    std::string _empty;
};

#endif // CONFOBJECT_H
