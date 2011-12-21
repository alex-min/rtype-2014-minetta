#ifndef IPADRESS_H
#define IPADRESS_H
#include <string>
#include <iostream>
#include "MyString.h"
#include "SystemDefines.h"
#include "LibC.h"
#ifdef OS_UNIX
#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/resource.h>
#elif defined OS_WINDOWS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <windows.h>
#else
#error "IpAdress.h: System not implemented yet"
#endif

namespace Network {
class IpAddress
{
public:
    IpAddress(const String &ip);
    IpAddress(const char *ip);
    IpAddress(Int8 a = 127, Int8 b = 0, Int8 c = 0, Int8 d = 1);
    void set(const String &ip);
    void set(Int8 a, Int8 b, Int8 c, Int8 d);
    void set(Int32 ip);
    String const & toString() const;
    Int8 const & toArray() const;
    Int32  toInt() const;
    static IpAddress getLocalAddress();
    void resolve(String const & hostname);



protected:
    Int8 _addr[4];
    String _str;
};
}

#endif // IPADRESS_H
