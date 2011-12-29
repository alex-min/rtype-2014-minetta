#ifndef CONNECTIONSLOT_H
#define CONNECTIONSLOT_H
#include "Protocol.h"
#include "Packet.h"
#include "ServerData.h"
#include "LoginMapper.h"

class ConnectionSlot : public Protocol::NetworkSlot
{
public:
    ConnectionSlot();
    void    sendConnected(Protocol::Protocol *, Network::Network *n,
                                 Protocol::StatusId stat, UInt16 id);
    virtual void onCall(bool isOnTimeout, Packet *packet, Protocol::Protocol *, void *);
};

#endif // CONNECTIONSLOT_H
