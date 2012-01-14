#include "DeadSlot.h"

void    DeadSlot::onCall(bool, Packet *p, Protocol::Protocol *proto, void *)
{
    LOGERR << "DIIEEEEE ! " << std::endl;
    ServerGame *game = reinterpret_cast<ServerGame *> (proto->getPointer());

    if (game) {
        LOGERR << "DIIEEEEE ! 2 (" << game->getMapper().getMapperList().size() << ")" << std::endl;

        PlayerInfo *pl = game->getMapper().getByNetwork(p->getNetwork());

        if (pl) {
            DeadSlot::sendDeadNotification(proto, pl->getId(), p->getNetwork());
        }
    }
}

void    DeadSlot::sendDeadNotification(Protocol::Protocol *p, UInt16 id, Network::Network *except)
{
    unsigned int size = 0;

    libc::Memadd(_tmpBuffer, &id, sizeof(UInt16), size);
    Protocol::LoginMapper::MapperType m = p->getLoginMapper().getMapperList();
    Protocol::LoginMapper::MapperType::iterator it;

    LOGERR << "++ here ++" << std::endl;
    for (it = m.begin(); it != m.end(); ++it)
    {
        LOGERR << "++ here2 ++" << std::endl;
        if ((*it)->getNetwork() != except)
        {
           LOGERR << "++ here3 ++" << std::endl;
           p->send((*it)->getNetwork(), Protocol::DEAD, _tmpBuffer, size);
        }
    }
}
