#ifndef JOINGAMESLOT_H
#define JOINGAMESLOT_H

#include "Protocol.h"
#include "Packet.h"
#include "ServerData.h"
#include "LoginMapper.h"
#include "ServerCore.h"

class JoinGameSlot : public Protocol::NetworkSlot
{
public:
    virtual void    onCall(bool isOnTimeout, Packet *packet, Protocol::Protocol *, void *);
    void            sendResponseJoinGame(Protocol::Protocol *, Network::Network *, ServerCore *,
                                         std::string const &, UInt16 packetId);
};

#endif // JOINGAMESLOT_H
