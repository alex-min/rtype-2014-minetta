#include "PlayerInfo.h"

UInt16 PlayerInfo::_playerCountId = 0;


PlayerInfo::PlayerInfo() :
    _login(""),
    _playerId(_playerCountId),
    _network(NULL)
{ ++_playerCountId; }

PlayerInfo::PlayerInfo(String const &login) :
    _login(login),
    _playerId(_playerCountId),
    _network(NULL),
    _player(NULL)
{ ++_playerCountId; }

PlayerInfo::PlayerInfo(Network::Network *net) :
    _login(""),
    _playerId(_playerCountId),
    _network(net),
    _player(NULL)
{ ++_playerCountId; }

PlayerInfo::PlayerInfo(UInt16 id) :
_login(""),
_playerId(id),
_network(NULL),
_player(NULL)
{ ++_playerCountId; }

IPlayer                     *PlayerInfo::getPlayer()
{
    return (_player);
}

String const &              PlayerInfo::getLogin() const
{
    return (_login);
}

UInt16                      PlayerInfo::getId() const
{
    return (_playerId);
}

Network::Network const *          PlayerInfo::getNetwork() const
{
    return (_network);
}

Network::Network *          PlayerInfo::getNetwork()
{
    return (const_cast<Network::Network *>(_network));
}

void                        PlayerInfo::setLogin(String const &login)
{
    _login = login;
}


void                        PlayerInfo::setId(UInt16 id)
{
    _playerId = id;
}


void                        PlayerInfo::setNetwork(Network::Network const *net)
{
    _network = net;
}

void                        PlayerInfo::setPlayer(IPlayer *player)
{
    _player = player;
}

void                        PlayerInfo::erase()
{
    _login = "";
    _network = NULL;
    _playerId = 0;
}
