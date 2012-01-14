#include "PopSlot.h"
#include <QMetaType>

PopSlot::PopSlot()
{

}

void    PopSlot::onCall(bool isOnTimeout, Packet *packet, Protocol::Protocol *proto, void *data)
{
    if (isOnTimeout || !packet || !proto || !data)
        return ;

    unsigned int tmpLen = 0;

    UInt16 id = libc::Memextract<UInt16>(packet->getData(), sizeof(UInt16), tmpLen);
    UInt8 monsterType = libc::Memextract<UInt8>(packet->getData(), sizeof(UInt8), tmpLen);
    UInt16 x = libc::Memextract<UInt16>(packet->getData(), sizeof(UInt16), tmpLen);
    UInt16 y = libc::Memextract<UInt16>(packet->getData(), sizeof(UInt16), tmpLen);
    Int32 date = libc::Memextract<Int32>(packet->getData(), sizeof(Int32), tmpLen);

    emit popMonster(id, monsterType, x, y, date);
}
