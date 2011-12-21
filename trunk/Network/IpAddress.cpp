#include "IpAddress.h"

namespace Network {
IpAddress::IpAddress(const String &ip)
{
    IpAddress::set(ip);
}

IpAddress::IpAddress(Int8 a, Int8 b, Int8 c, Int8 d)
{
    IpAddress::set(a, b, c, d);
}

IpAddress::IpAddress(const char *ip)
{
    IpAddress::set(ip);
}

void IpAddress::set(Int32 ip) {
    _addr[0] = ip & 0xff;
    ip >>= 8;
    _addr[1] = ip & 0xff;
    ip >>= 8;
    _addr[2] = ip & 0xff;
    ip >>= 8;
    _addr[3] = ip & 0xff;
}

void IpAddress::set(const String &ip)
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

void IpAddress::set(Int8 a, Int8 b, Int8 c, Int8 d)
{
    _addr[0] = a;
    _addr[1] = b;
    _addr[2] = c;
    _addr[3] = d;
}

 String const & IpAddress::toString() const
{
    const_cast<String &> (_str) =
            String::byteToString(_addr[0]) + "." +
            String::byteToString(_addr[1]) + "." +
            String::byteToString(_addr[2]) + "." +
            String::byteToString(_addr[3]);
    return (_str);
}

Int8 const & IpAddress::toArray() const
{
    return (*_addr);
}

Int32  IpAddress::toInt() const
{
    return (_addr[0] | (_addr[1] << 8) | (_addr[2] << 16) | (_addr[3] << 24));
}

void IpAddress::resolve(String const & hostname)
{
#ifdef OS_WINDOWS
    struct hostent * record = gethostbyname(hostname.c_str());
    in_addr * address = (in_addr * )record->h_addr;
    char * ip_address = inet_ntoa(* address);
    IpAddress::set(ip_address);
#elif defined OS_UNIX
    struct hostent * record = gethostbyname(hostname.c_str());
    in_addr * address = (in_addr * )record->h_addr;
    char * ip_address = inet_ntoa(* address);
    IpAddress::set(ip_address);
#endif
}

IpAddress IpAddress::getLocalAddress()
{
#ifdef OS_WINDOWS
std::cerr << "IpAddress::getLocalAddress() : Win32Implementation is broken" << std::endl;
#elif defined OS_UNIX
std::cerr << "IpAddress::getLocalAddress() : UNIXImplementation is broken" << std::endl;
#else
#error "Unknown Operating System on IpAddress::getLocalAddress()"
#endif
    return (IpAddress());
}

} // !Namespace : Network

