#include "ConfObject.h"

ConfObject::ConfObject(std::string const &addr)
{
    _file = addr;
    _empty = "";
}

void ConfObject::putLineInDico(std::string const &str)
{
    std::string key;
    std::string value;
    int sep;

    sep = str.find('=', 0);
    key = str.substr(0, sep);
    value = str.substr(sep + 1);
    _dico[key] = value;
}

std::string const &ConfObject::getStringValueOf(std::string const &key) const
{
    std::map<std::string, std::string>::const_iterator it;

    for (it = _dico.begin(); it != _dico.end(); ++it)
      {
        if ((*it).first.compare(key) == 0)
          return ((*it).second);
      }
    throw Exception("Cannot find " + key + " in conf file");
}

UInt16        ConfObject::getSize() const
{
    return (_dico.size());
}


const std::string & ConfObject::at(UInt16 at) const
{
    if (at >= _dico.size())
        return (_empty);
    UInt32 i = 0;
    for (std::map<std::string, std::string>::const_iterator it = _dico.begin(); it != _dico.end();
         ++it) {
        if (at == i)
            return (it->first);
        ++i;
    }
    return (_empty);

}

