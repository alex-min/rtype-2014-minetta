#ifndef ENDGAMESLOT_H
#define ENDGAMESLOT_H

#include "Protocol.h"
#include "Packet.h"
#include "ServerData.h"
#include "LoginMapper.h"
#include "ServerCore.h"

class EndGameSlot : public Protocol::NetworkSlot
{
public:
    virtual void    onCall(bool isOnTimeout, Packet *packet, Protocol::Protocol *, void *);
    void            sendEndGameNotification(Protocol::Protocol *, Protocol::StatusId);

};

#endif // ENDGAMESLOT_H
