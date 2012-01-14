#ifndef DEADSLOT_H
#define DEADSLOT_H

#include "Protocol.h"
#include "Packet.h"
#include "ServerData.h"
#include "LoginMapper.h"
#include "ServerCore.h"

class DeadSlot : public Protocol::NetworkSlot
{
public:
    virtual void    onCall(bool isOnTimeout, Packet *packet, Protocol::Protocol *, void *);
    void            sendDeadNotification(Protocol::Protocol *, UInt16 id, Network::Network *except);

};

#endif // DEADSLOT_H
