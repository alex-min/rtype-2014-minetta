#include "MoveSlot.h"

void         MoveSlot::sendMove(Protocol::Protocol *proto, Network::Network *n,
                      UInt16 loginId,
                      UInt16 x, UInt16 y)
{
    unsigned int tmpLen = 0;
    libc::Memadd(_tmpBuffer, &loginId, sizeof(UInt16), tmpLen);
    libc::Memadd(_tmpBuffer, &x, sizeof(UInt16), tmpLen);
    libc::Memadd(_tmpBuffer, &y, sizeof(UInt16), tmpLen);
    proto->send(n, Protocol::MOVE, _tmpBuffer, tmpLen);
}

void MoveSlot::onCall(bool, Packet *packet, Protocol::Protocol *proto, void *c)
{
    //LOGERR << "moveSlot" << std::endl;
    unsigned int sizeCount = 0;
    UInt16 x = libc::Memextract<UInt16>(packet->getData(), sizeof(UInt16), sizeCount);
    UInt16 y = libc::Memextract<UInt16>(packet->getData(), sizeof(UInt16), sizeCount);
    if (proto->getLoginMapper().getByNetwork(packet->getNetwork()) == 0)
    {
       // TODO : remove this

        MoveSlot::sendMove(proto,
                           const_cast<Network::Network *> (packet->getNetwork()),
                           5, x + 100, y);
        MoveSlot::sendMove(proto,
                           const_cast<Network::Network *> (packet->getNetwork()),
                           6, x - 100, y);
        MoveSlot::sendMove(proto,
                           const_cast<Network::Network *> (packet->getNetwork()),
                           7, x + y, x + 100);
        return ;
    }
    UInt16 playerId = proto->getLoginMapper().getByNetwork(packet->getNetwork())->getId();
    ServerCore *core = reinterpret_cast<ServerCore *> (c);
    Protocol::LoginMapper::MapperType &mapList = proto->getLoginMapper().getMapperList();
    for (Protocol::LoginMapper::MapperType::iterator it = mapList.begin();
         it != mapList.end(); ++it) {
        if ((*it)->getNetwork() != packet->getNetwork()) {
            MoveSlot::sendMove(proto,
                               const_cast<Network::Network *> ((*it)->getNetwork()),
                               playerId, x, y);
        }
    }
    (void) core;
}
