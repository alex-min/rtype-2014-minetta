#include "LoginMapper.h"

namespace Protocol {
LoginMapper::LoginMapper() :
    _invalidString("")
{
}

String const & LoginMapper::getLogin(Network::Network const *net) const
{
    return (LoginMapper::getLogin(const_cast<Network::Network *> (net)->getSocket()->getRemoteIp(),
                                  const_cast<Network::Network *> (net)->getSocket()->getPort()
                                  ));
}

String const & LoginMapper::getLogin(Network::IpAddress const &addr, UInt16 port) const
{
    UInt64 checkIp = addr.toInt();
    UInt64 checkPort = port;
    checkPort <<= 32;
    checkIp |= checkPort;
    std::map< UInt64, String >::const_iterator it;
    it = _mapping.find(checkIp);
    if (it == _mapping.end())
        return (_invalidString);
    return (it->second);
}

void        LoginMapper::setLogin(String const &login, Network::Network const *net)
{

}

} // !namespace : Protocol
