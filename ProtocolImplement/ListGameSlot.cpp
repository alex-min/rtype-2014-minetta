#include "ListGameSlot.h"

void    ListGameSlot::onCall(bool, Packet *packet, Protocol::Protocol *proto, void *c)
{
    sendListGame(proto, packet->getNetwork(), reinterpret_cast<ServerCore *> (c), packet->getHeader()._packetId);
}

void    ListGameSlot::sendListGame(Protocol::Protocol *p, Network::Network *n, ServerCore *c, UInt16 packetId)
{
    PoolFactory< ServerGame >::ListType const &games = c->getGamePool().getMapList();

    for (PoolFactory< ServerGame>::ListType::const_iterator it = games.begin();
         it != games.end(); ++it)
    {
        LOG << "here" << std::endl;
        if (it->second == false) {
            LOG << "real" << std::endl;
            ServerGame const *g = it->first;
            LOG << (void *) g << std::endl;
            unsigned int nbPl = g->getMapperList().size();
            unsigned int maxPl = g->getMaxNbPlayer();
            unsigned int size = 0;



            libc::Memadd(_tmpBuffer, &nbPl, sizeof(UInt8), size);
            libc::Memadd(_tmpBuffer, &maxPl, sizeof(UInt8), size);
            libc::Memadd(_tmpBuffer, g->getName().c_str(), g->getName().size() + 1, size);
            p->send(n, Protocol::LIST_GAME, _tmpBuffer, size, packetId);
        }
    }
}
