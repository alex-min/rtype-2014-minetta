#include "LoginMapper.h"

namespace Protocol {
LoginMapper::LoginMapper() :
    _playerId(0),
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
    std::map< UInt64, std::pair<String, UInt16 > >::const_iterator it;
    it = _mapping.find(checkIp);
    if (it == _mapping.end())
        return (_invalidString);
    return (it->second.first);
}

void        LoginMapper::setLogin(String const &login, Network::Network const *net)
{
    if (net && net->getSocket())
        LoginMapper::setLogin(login, net->getSocket()->getRemoteIp(),
                              net->getSocket()->getRemotePort());
}

void        LoginMapper::setLogin(String const &login, Network::IpAddress const &addr, UInt16 port)
{
    UInt64 checkIp = addr.toInt();
    UInt64 checkPort = port;
    checkPort <<= 32;
    checkIp |= checkPort;
    _mapping[checkIp] = std::pair<String, UInt16 > (login, _playerId);
    _playerId++;
}

} // !namespace : Protocol
