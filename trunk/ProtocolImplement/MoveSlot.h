#ifndef MOVESLOT_H
#define MOVESLOT_H
#include "Protocol.h"
#include "Packet.h"
#include "ServerData.h"
#include "LoginMapper.h"
#include "ServerCore.h"

class MoveSlot : public Protocol::NetworkSlot {
    void         sendMove(Protocol::Protocol *, Network::Network *,
                          UInt16 loginId,
                          UInt16 x, UInt16 y);
    virtual void onCall(bool isOnTimeout, Packet *packet, Protocol::Protocol *, void *);
};

#endif // MOVESLOT_H
