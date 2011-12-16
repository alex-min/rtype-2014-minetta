#include "IpAddress.h"

namespace Network {
IpAddress::IpAddress(const std::string &ip)
{
}

IpAddress::IpAddress(Int8 a, Int8 b, Int8 c, Int8 d)
{
    _addr[0] = a;
    _addr[1] = b;
    _addr[2] = c;
    _addr[3] = d;
}

const std::string & IpAddress::toString() const
{
    std::cerr << "TODO: Fix IpAddress::toString()" << std::endl;
    const_cast<std::string &>(_str) = "127.0.0.1";
    return (_str);
}

Int8 const & IpAddress::toArray() const
{
    return (*_addr);
}

IpAddress IpAddress::getLocalAddress()
{

}
}

