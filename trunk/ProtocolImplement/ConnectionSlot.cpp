#include "ConnectionSlot.h"

ConnectionSlot::ConnectionSlot()
{
}

void ConnectionSlot::onCall(bool isOnTimeout, Packet *packet, Protocol::Protocol *proto)
{
    (void) isOnTimeout;
    if (!packet || !proto)
        return ;
    Protocol::StatusId _s;
    _s = Protocol::OK;
    proto->send(packet->getNetwork(), Protocol::STATUS, &_s, sizeof(Protocol::StatusId));
    LOGERR << "here" << std::endl;
}
