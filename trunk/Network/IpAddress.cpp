#include "IpAddress.h"

namespace Network {
IpAddress::IpAddress(const String &ip)
{
    unsigned int i = 0;
    libc::Memset(&_addr, 0, 4 * sizeof(Int8));
    const std::vector<String> *s = ip.split('.');
    for (std::vector<String>::const_iterator it = s->begin(); it != s->end(); ++it) {
        _addr[i] = it->toInt();
        ++i;
    }
    delete s;
}

IpAddress::IpAddress(Int8 a, Int8 b, Int8 c, Int8 d)
{
    _addr[0] = a;
    _addr[1] = b;
    _addr[2] = c;
    _addr[3] = d;
}

const String & IpAddress::toString() const
{
    const_cast<String &>(_str) =
            String::toString(_addr[0]) + "." +
            String::toString(_addr[1]) + "." +
            String::toString(_addr[2]) + "." +
            String::toString(_addr[3]);
    return (_str);
}

Int8 const & IpAddress::toArray() const
{
    return (*_addr);
}

IpAddress IpAddress::getLocalAddress()
{
}

} // !Namespace : Network

