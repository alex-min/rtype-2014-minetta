#ifndef CREATEGAMESLOT_H
#define CREATEGAMESLOT_H
#include "Protocol.h"
#include "Packet.h"
#include "ServerData.h"
#include "LoginMapper.h"
#include "ServerCore.h"

class CreateGameSlot : public Protocol::NetworkSlot
{
public:
    virtual void onCall(bool isOnTimeout, Packet *packet, Protocol::Protocol *, void *);
};

#endif // CREATEGAMESLOT_H
