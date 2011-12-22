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
    void        setLogin(String const &login, Network::IpAddress const &addr, UInt16 port);

protected:
    std::map<UInt64, std::pair<String, UInt16 > > _mapping;
    UInt16                                        _playerId;
    String const &                                _invalidString;
};
} // !namespace : Protocol

#endif // LOGINMAPPER_H
