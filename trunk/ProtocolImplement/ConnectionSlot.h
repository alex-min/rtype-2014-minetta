#ifndef CONNECTIONSLOT_H
#define CONNECTIONSLOT_H
#include "Protocol.h"
#include "Packet.h"

class ConnectionSlot : public Protocol::NetworkSlot
{
public:
    ConnectionSlot();
    virtual void onCall(bool isOnTimeout, Packet *packet, Protocol::Protocol *);
};

#endif // CONNECTIONSLOT_H
