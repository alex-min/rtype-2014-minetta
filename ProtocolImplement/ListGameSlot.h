#ifndef LISTGAMESLOT_H
#define LISTGAMESLOT_H

#include "Protocol.h"
#include "Packet.h"
#include "ServerData.h"
#include "LoginMapper.h"
#include "ServerCore.h"

class ListGameSlot : public Protocol::NetworkSlot
{
public:
    virtual void    onCall(bool isOnTimeout, Packet *packet, Protocol::Protocol *, void *);
    void            sendListGame(Protocol::Protocol *, Network::Network *, ServerCore *, UInt16);
};

#endif // LISTGAMESLOT_H
