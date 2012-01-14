#include "PongSlot.h"

void    PongSlot::onCall(bool, Packet *, Protocol::Protocol *, void *)
{

}

void    PongSlot::pongResp(bool timeOut, Packet *p, Protocol::Protocol *proto)
{
    if (timeOut)
        proto->onDisconnect(p->getNetwork());
}

void    PongSlot::sendPing(Protocol::Protocol *p, Network::Network *n)
{
    p->registerNextPacket(n, this, reinterpret_cast<Protocol::SlotCall>(&PongSlot::pongResp));
    p->send(n, Protocol::PING, "", 0);
}
