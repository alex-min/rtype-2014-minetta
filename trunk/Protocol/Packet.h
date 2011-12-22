#ifndef PACKET_H
#define PACKET_H
#include "Network.h"
#include "Protocol.h"
#include "NetworkSlot.h"

class Packet
{
public:
    Packet(Network::Network *net = NULL,
           Protocol::NetworkPacket::NetworkHeader *head = NULL,
           UInt64 timemout = Protocol::DEFAULT_TIMEOUT,
           Protocol::NetworkSlot *netSlot = NULL,
           Protocol::SlotCall netSlotCall = NULL);

    Network::Network *                          getNetwork() const;
    Protocol::NetworkPacket::NetworkHeader *    getHeader() const;
    UInt64                                      getTimeout() const;
    void                                        setNetwork(Network::Network *);
    void                                        setTimeout(UInt64 timeout);
    void                                        setHeader(Protocol::NetworkPacket::NetworkHeader *);

protected:
    Network::Network                       *     _net;
    Protocol::NetworkPacket::NetworkHeader *     _header;
    UInt64                                       _timeout;
    Protocol::NetworkSlot                  *     _netSlot;
    Protocol::SlotCall                           _netSlotCall;
};

#endif // PACKET_H
