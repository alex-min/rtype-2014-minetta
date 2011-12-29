#include "LoginMapper.h"

namespace Protocol {
LoginMapper::LoginMapper() :
    _playerId(0),
    _invalidString("")
{
}

PlayerInfo     *LoginMapper::getByLogin(String const &login)
{
    for (MapperType::iterator it = _mapping.begin(); it != _mapping.end();
         ++it) {
        if ((*it)->getLogin() == login) {
            return (*it);
        }
    }
    return (NULL);
}

PlayerInfo     *LoginMapper::getByNetwork(Network::Network const * network)
{
    for (MapperType::iterator it = _mapping.begin(); it != _mapping.end();
         ++it) {
        if ((*it)->getNetwork() == network) {
            return (*it);
        }
    }
    return (NULL);
}

PlayerInfo     *LoginMapper::getById(UInt16 id)
{
    for (MapperType::iterator it = _mapping.begin(); it != _mapping.end();
         ++it) {
        if ((*it)->getId() == id) {
            return (*it);
        }
    }
    return (NULL);
}


bool        LoginMapper::exist(String const &login)
{
    PlayerInfo *p = LoginMapper::getByLogin(login);
    if (!p)
        return (false);
    return (true);
}


} // !namespace : Protocol
