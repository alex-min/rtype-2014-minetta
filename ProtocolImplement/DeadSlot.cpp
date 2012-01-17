#include "DeadSlot.h"

void    DeadSlot::onCall(bool, Packet *p, Protocol::Protocol *proto, void *c)
{
    ServerGame *game = reinterpret_cast<ServerGame *> (proto->getPointer());
    ServerCore *core = reinterpret_cast<ServerCore *> (c);

    if (game) {
        PlayerInfo *pl = game->getMapper().getByNetwork(p->getNetwork());

        if (pl) {
            DeadSlot::sendDeadNotification(proto, pl->getId(), p->getNetwork());
        }

        pl->die();
        if (game->getMapper().getAlivePlayerCount() == 0) {
            LOG << "Game is now at ENNND !" << std::endl;
            proto->send(p->getNetwork(), Protocol::END_GAME,
                                      "h", 1);
            for (unsigned int i = 0; i < 3; i++)
                game->run();
            game->kill();
            core->removeGame(game);
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
