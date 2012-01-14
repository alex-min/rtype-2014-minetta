#include "CreateGameSlot.h"

CreateGameSlot::CreateGameSlot()
{

}

void    CreateGameSlot::createGame(Protocol::Protocol *proto, Network::Network *net, std::string const &gameName, char mapId, char nbPlayers)
{
    UInt8        map_id = mapId - '0';
    UInt8        nb_players = nbPlayers - '0';

    unsigned int tmpLen = 0;

    libc::Memadd(_tmpBuffer, gameName.c_str(), gameName.size() + 1, tmpLen);
    libc::Memadd(_tmpBuffer, &map_id, sizeof(UInt8), tmpLen);
    libc::Memadd(_tmpBuffer, &nb_players, sizeof(UInt8), tmpLen);

    proto->send(net, Protocol::CREATE_GAME, _tmpBuffer, tmpLen);
}

void CreateGameSlot::onCall(bool isOnTimeout, Packet *packet, Protocol::Protocol *proto, void *data)
{
    std::cout << "Game Creation" << std::endl;
    if (isOnTimeout || !packet || !proto || !data)
        return ;

    unsigned int tmpLen = 0;

    Protocol::StatusId status = libc::Memextract<Protocol::StatusId>(packet->getData(), sizeof(Protocol::StatusId), tmpLen);

    bool ok = false;

    if (status == Protocol::OK)
        ok = true;

    std::cout << "Game Creation" << std::endl;

    emit gameCreation(ok);
}
