#include "LoginMapper.h"

namespace Protocol {
LoginMapper::LoginMapper() :
    _playerId(0),
    _invalidString("")
{
}

UInt32          LoginMapper::getAlivePlayerCount() const
{
    UInt32      alive = 0;

    for (MapperType::const_iterator it = _mapping.begin(); it != _mapping.end();
         ++it) {
        if ((*it)->isDead() == false)
            ++alive;
    }
    return (alive);
}

LoginMapper::MapperType     &LoginMapper::getMapperList()
{
    return (_mapping);
}

LoginMapper::MapperType const     &LoginMapper::getMapperList() const
{
    return (_mapping);
}

PlayerInfo     *LoginMapper::getByLogin(String const &login)
{
    for (MapperType::iterator it = _mapping.begin(); it != _mapping.end();
         ++it) {
        LOGERR << "LOGIN : " << (*it)->getLogin() << std::endl;
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

PlayerInfo     *LoginMapper::addPlayer(String const &login)
{
    if (!LoginMapper::exist(login)) {
    PlayerInfo *p = _playerPool.generate();
    p->setLogin(login);
    p->setId(_playerId);
    _playerId++;
    _mapping.push_back(p);
    return (p);
    }
    return (NULL);
}

PlayerInfo     *LoginMapper::addPlayer(PlayerInfo *p)
{
    _playerId++;
    _mapping.push_back(p);
    return (p);
}


PlayerInfo     *LoginMapper::addPlayer(Network::Network const *network)
{
    _playerId++;
    PlayerInfo *p = _playerPool.generate();
    _mapping.push_back(p);
    p->setNetwork(network);
    return (p);
}

PlayerInfo     *LoginMapper::addPlayer(UInt16 id)
{
    _playerId++;
    PlayerInfo *p = _playerPool.generate();
    _mapping.push_back(p);
    p->setId(id);
    return (p);
}

void            LoginMapper::removePlayer(PlayerInfo *pl)
{
    if (!pl)
        return ;
    _mapping.remove(pl);
}

} // !namespace : Protocol
