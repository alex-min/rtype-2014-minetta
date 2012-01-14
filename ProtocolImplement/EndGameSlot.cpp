#include "EndGameSlot.h"

void    EndGameSlot::onCall(bool, Packet *, Protocol::Protocol *, void *)
{

}

void    EndGameSlot::sendEndGameNotification(Protocol::Protocol *p, Protocol::StatusId status)
{
    unsigned int size = 0;

    libc::Memadd(_tmpBuffer, &status, sizeof(Protocol::StatusId), size);
    Protocol::LoginMapper::MapperType m = p->getLoginMapper().getMapperList();
    Protocol::LoginMapper::MapperType::iterator it;

    for (it = m.begin(); it != m.end(); ++it)
    {
        p->send((*it)->getNetwork(), Protocol::END_GAME, _tmpBuffer, size);
    }
}
