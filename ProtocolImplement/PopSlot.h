#ifndef POPSLOT_H
#define POPSLOT_H

#include "Protocol.h"
#include "Packet.h"
#include "ServerData.h"
#include "LoginMapper.h"
#include "ServerCore.h"


class PopSlot : public Protocol::NetworkSlot
{
public:
    virtual void    onCall(bool isOnTimeout, Packet *packet, Protocol::Protocol *, void *);
    void            sendPop(Protocol::Protocol *, Network::Network *,
                            UInt16 popId,
                            UInt8 monsterType,
                            UInt16 shootPosX,
                            UInt16 shootPosY,
                            UInt32 date);
};

#endif // POPSLOT_H
