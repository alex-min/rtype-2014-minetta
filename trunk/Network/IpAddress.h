#ifndef IPADRESS_H
#define IPADRESS_H
#include <string>
#include <iostream>
#include "String.h"

namespace Network {
class IpAddress
{
public:
    IpAddress(const std::string &ip = "");
    IpAddress(Int8, Int8, Int8, Int8);
    IpAddress();
    const std::string & toString() const;
    Int8 const & toArray() const;
    static IpAddress getLocalAddress();



protected:
    Int8 _addr[4];
    std::string _str;
};
}

#endif // IPADRESS_H
