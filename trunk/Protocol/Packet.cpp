#include "Packet.h"

Packet::Packet(Network::Network *net,
       Protocol::NetworkPacket::NetworkHeader *head,
       UInt64 timemout,
               Protocol::NetworkSlot *netSlot,
               Protocol::SlotCall netSlotCall) :
        _net(net),
        _timeout(timemout),
        _netSlot(netSlot),
        _netSlotCall(netSlotCall)
{
    if (head) {
        libc::Memcpy(&_header, head, sizeof(Protocol::NetworkPacket::NetworkHeader));
    }
}

Network::Network *                          Packet::getNetwork() const
{

    return (_net);
}

Protocol::NetworkPacket::NetworkHeader &    Packet::getHeader()
{
    return (_header);
}

Protocol::NetworkPacket::NetworkHeader const &    Packet::getHeader() const
{
    return (_header);
}

UInt64                                      Packet::getTimeout() const
{
    return (_timeout);
}

Protocol::NetworkSlot                       *Packet::getSlot()
{
    return (_netSlot);
}

Protocol::SlotCall                          Packet::getSlotCall()
{
    return (_netSlotCall);
}

void                                        Packet::setNetwork(Network::Network *net)
{
    _net = net;
}

void                                        Packet::setTimeout(UInt64 timeout)
{
    _timeout = timeout;
}

void                                        Packet::setHeader(Protocol::NetworkPacket::NetworkHeader *head)
{
    if (head) {
        libc::Memcpy(&_header, head, sizeof(Protocol::NetworkPacket::NetworkHeader));
    }
}

void                                        Packet::setSlot(Protocol::NetworkSlot *slot)
{
    _netSlot = slot;
}

void                                        Packet::setSlotCall(Protocol::SlotCall slotCall)
{
    _netSlotCall =  slotCall;
}

void                                        Packet::erase()
{
    libc::ZeroMemory(&_header, sizeof(Protocol::NetworkPacket::NetworkHeader));
    _net = 0;
    _timeout = Protocol::DEFAULT_TIMEOUT;
    _netSlot = 0;
    _netSlotCall = 0;
}
