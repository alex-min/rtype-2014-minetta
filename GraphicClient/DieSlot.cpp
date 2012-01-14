#include "DieSlot.h"

DieSlot::DieSlot()
{

}

void    DieSlot::sendDie(Protocol::Protocol *proto, Network::Network *net)
{
    proto->send(net, Protocol::DEAD, _tmpBuffer, 1);
}

void DieSlot::onCall(bool isOnTimeout, Packet *packet, Protocol::Protocol *proto, void *data)
{
    if (isOnTimeout || !packet || !proto || !data)
        return;

    unsigned int tmpLen = 0;

    UInt16 playerId = libc::Memextract<UInt16>(packet->getData(), sizeof(UInt16), tmpLen);

    qRegisterMetaType<UInt16>("UInt16");

    emit die(playerId);
}
