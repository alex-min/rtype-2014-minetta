#include "PopSlot.h"

 void    PopSlot::onCall(bool, Packet *p, Protocol::Protocol *proto, void *c) {

     unsigned int sizeCount = 0;
     UInt16 x = libc::Memextract<UInt16>(p->getData(), sizeof(UInt16), sizeCount);
     UInt16 y = libc::Memextract<UInt16>(p->getData(), sizeof(UInt16), sizeCount);
     ServerGame *g = reinterpret_cast < ServerGame *> (proto->getPointer());
     if (g) {
         Protocol::LoginMapper::MapperType &map = g->getMapperList();
         for (Protocol::LoginMapper::MapperType::iterator it = map.begin();
              it != map.end(); ++it) {
            if ((*it)->getNetwork() != p->getNetwork()) {
               PopSlot::sendPop(proto,
                                (*it)->getNetwork(),
                                g->generateId(),
                                0,x,y,0);
            }
         }
     }
}

void            PopSlot::sendPop(Protocol::Protocol *p, Network::Network *n,
                        UInt16 popId,
                        UInt8 monsterType,
                        UInt16 shootPosX,
                        UInt16 shootPosY,
                        UInt32 date)
{
    unsigned int tmpLen = 0;
    libc::Memadd(_tmpBuffer, &popId, sizeof(UInt16), tmpLen);
    libc::Memadd(_tmpBuffer, &monsterType, sizeof(UInt8), tmpLen);
    libc::Memadd(_tmpBuffer, &shootPosX, sizeof(UInt16), tmpLen);
    libc::Memadd(_tmpBuffer, &shootPosY, sizeof(UInt16), tmpLen);
    libc::Memadd(_tmpBuffer, &date, sizeof(UInt32), tmpLen);
  //  LOG << "Sending pop to " << n << std::endl;
    p->send(n, Protocol::POP, _tmpBuffer, tmpLen);
}
