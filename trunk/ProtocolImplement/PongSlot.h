#ifndef PONGSLOT_H
#define PONGSLOT_H

#include "Protocol.h"
#include "Packet.h"
#include "ServerData.h"
#include "LoginMapper.h"
#include "ServerCore.h"

class PongSlot : public Protocol::NetworkSlot
{
public:
    virtual void    onCall(bool isOnTimeout, Packet *packet, Protocol::Protocol *, void *);
    void            sendPing(Protocol::Protocol *, Network::Network *);
    void            pongResp(bool, Packet*, Protocol::Protocol *);
};

#endif // PONGSLOT_H
