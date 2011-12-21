#ifndef LOGINMAPPER_H
#define LOGINMAPPER_H
#include <map>
#include "Network.h"
#include "MyString.h"
#include "SystemDefines.h"

namespace Protocol {
class LoginMapper
{
public:
    LoginMapper();
    String const & getLogin(Network::Network const *net) const;
    String const & getLogin(Network::IpAddress const &addr, UInt16 port) const;
    void        setLogin(String const &login, Network::Network const *net);

protected:
    std::map<UInt64, String> _mapping;
    String const & _invalidString;
};
} // !namespace : Protocol

#endif // LOGINMAPPER_H
