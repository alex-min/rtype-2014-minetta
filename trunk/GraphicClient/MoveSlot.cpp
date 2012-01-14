#include "MoveSlot.h"
#include <QString>

MoveSlot::MoveSlot()
{

}

void MoveSlot::onCall(bool isOnTimeout, Packet *packet, Protocol::Protocol *proto, void *data)
{
    if (isOnTimeout || !packet || !proto || !data)
        return;

    unsigned int tmpLen = 0;

    UInt16 id = libc::Memextract<UInt16>(packet->getData(), sizeof(UInt16), tmpLen);
    UInt16 x = libc::Memextract<UInt16>(packet->getData(), sizeof(UInt16), tmpLen);
    UInt16 y = libc::Memextract<UInt16>(packet->getData(), sizeof(UInt16), tmpLen);

    emit posChanged(id, x, y);
}

void    MoveSlot::sendNewPlayerPos(Protocol::Protocol *proto, Network::Network *net, float x, float y)
{
    UInt16  tmpX = static_cast<UInt16>(x);
    UInt16  tmpY = static_cast<UInt16>(y);
    unsigned int tmpLen = 0;

    libc::Memadd(_tmpBuffer, &tmpX, sizeof(UInt16), tmpLen);
    libc::Memadd(_tmpBuffer, &tmpY, sizeof(UInt16), tmpLen);

    proto->send(net, Protocol::MOVE, _tmpBuffer, tmpLen);
}
