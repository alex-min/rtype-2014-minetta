#ifndef IPADRESS_H
#define IPADRESS_H
#include <string>
#include <iostream>
#include "String.h"
#include "SystemDefines.h"
#include "LibC.h"

namespace Network {
class IpAddress
{
public:
    IpAddress(const String &ip = "");
    IpAddress(Int8, Int8, Int8, Int8);
    IpAddress();
    const String & toString() const;
    Int8 const & toArray() const;
    static IpAddress getLocalAddress();



protected:
    Int8 _addr[4];
    String _str;
};
}

#endif // IPADRESS_H
