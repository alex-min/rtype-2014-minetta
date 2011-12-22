#include "Packet.h"

Packet::Packet(Network::Network *net,
       Protocol::NetworkPacket::NetworkHeader *head,
       UInt64 timemout,
               Protocol::NetworkSlot *netSlot,
               Protocol::SlotCall netSlotCall) :
        _net(net),
        _header(head),
        _timeout(timemout),
        _netSlot(netSlot),
        _netSlotCall(netSlotCall)
{
}

Network::Network *                          Packet::getNetwork() const
{

    return (_net);
}

Protocol::NetworkPacket::NetworkHeader *    Packet::getHeader() const
{
    return (_header);
}

UInt64                                      Packet::getTimeout() const
{
    return (_timeout);
}

void                                        Packet::setNetwork(Network::Network *net)
{
    _net = net;
}

void                                        Packet::setTimeout(UInt64 timeout)
{
    _timeout = timeout;
}

void                                        Packet::setHeader(Protocol::NetworkPacket::NetworkHeader *h)
{
    _header = h;
}
