#include "PlayerInfo.h"

PlayerInfo::PlayerInfo() :
    _login(""),
    _playerId(0xffff),
    _network(NULL)
{
}

String const &              PlayerInfo::getLogin() const
{
    return (_login);
}

UInt16                      PlayerInfo::getId() const
{
    return (_playerId);
}

Network::Network *          PlayerInfo::getNetwork() const
{
    return (_network);
}
