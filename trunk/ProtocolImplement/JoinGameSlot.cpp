#include "JoinGameSlot.h"

void    JoinGameSlot::onCall(bool, Packet *packet, Protocol::Protocol *proto, void *c)
{
    std::string const & gameName = proto->getLoginFromData(packet->getData(), packet->getHeader()._len);
    sendResponseJoinGame(proto, packet->getNetwork(), reinterpret_cast<ServerCore *> (c),
                         gameName, packet->getHeader()._packetId);
}

void    JoinGameSlot::sendResponseJoinGame(Protocol::Protocol *p, Network::Network *n, ServerCore *c,
                                           std::string const &gameName, UInt16 packetId)
{
    ServerGame *g = c->getMapByName(gameName);

    Protocol::StatusId  status;
    status = ((g) ? ((g->getMapperList().size() < g->getMaxNbPlayer()) ? Protocol::OK : Protocol::GAME_FULL) : Protocol::FAILED);

    unsigned int size = 0;
    libc::Memadd(_tmpBuffer, &status, sizeof(int), size);

    if (g)
    {
        UInt16 port = g->getGamePort();
        libc::Memadd(_tmpBuffer, &port, sizeof(UInt16), size);
        LOG << "Port : " << port << std::endl;
    }
    LOG << "Size : " << size << std::endl;
    p->send(n, Protocol::REF_GAME, _tmpBuffer, size, packetId);
}
