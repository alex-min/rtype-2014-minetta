#include "Protocol.h"
#include "Packet.h"

namespace Protocol {
Protocol::Protocol() :
    _mainBuffer(new char[MAX_READ_SIZE]),
    _packetCount(1)
{
}

Protocol::~Protocol() {
    delete [] _mainBuffer;
}

LoginMapper &   Protocol::getLoginMapper()
{
    return (_mapper);
}


void Protocol::onClientConnected(Network::Network *remote, Network::Network *client)
{
    (void) remote;
    (void) client;
}

void Protocol::onRead(Network::Network *remote, Network::Network *client)
{
    (void) remote;
    if (client->getReadBuffer()->getByteKeep() != HEADBYTE)
        client->getReadBuffer()->extractKeepDelim(_mainBuffer, MAX_READ_SIZE, HEADBYTE);
    if (client->getReadBuffer()->getReadSize() < sizeof(NetworkPacket::NetworkHeader))
        return ;
    client->getReadBuffer()->extractKeep(_mainBuffer, MAX_READ_SIZE);
    _extractedHeader = reinterpret_cast<NetworkPacket::NetworkHeader *> (_mainBuffer);
    if (!(Protocol::isValidPacket()))
    {
        client->getReadBuffer()->getByte(); // on retire le 1er octet pour virer le header
        Protocol::onRead(remote, client); // on rappelle pour reparser la suite
        return ;
    }
    client->getReadBuffer()->extract(_mainBuffer,  _extractedHeader->_len);
    Protocol::dispatchPacket(client);
}

void            Protocol::unregisterPacket(Packet *p)
{
    _packetMap.remove(p);
    _packetFactory.invalidate(p);
}

void            Protocol::registerNextPacket(Network::Network *net, NetworkSlot *slot, SlotCall call,
                                   UInt16 timeout)
{
    Packet *p = _packetFactory.generate();
    p->setNetwork(net);
    p->setTimeout(timeout);
    p->setSlot(slot);
    p->setSlotCall(call);
    p->getHeader()._packetId = _packetCount;
    _packetMap.push_back(p);
}

void            Protocol::registerSlotType(SlotType type, NetworkSlot *slot)
{
    _slotPacketMap[type] = slot;
}

void            Protocol::send(Network::Network *net, SlotType packetType,
                     const void *content, UInt16 len)
{
    _sendingHeader._begin = HEADBYTE;
    _sendingHeader._slotType = packetType;
    _sendingHeader._packetId = _packetCount;
    _sendingHeader._len = sizeof(NetworkPacket::NetworkHeader) + len;
    _sendingHeader._checksum = 0x4242; // TODO : fix this
    _sendingHeader._checksumData = 0x4242; // TODO : fix this

    net->getWriteBuffer()->append(&_sendingHeader, sizeof(NetworkPacket::NetworkHeader));
    net->getWriteBuffer()->append(content, len);
    _packetCount++;
}

void            Protocol::dispatchPacket(Network::Network *caller)
{
    (void) caller;
    Packet *packetRegistred = Protocol::getPacketFrom(caller, _extractedHeader->_packetId);
    if (packetRegistred) {
        packetRegistred->setHeader(_extractedHeader);
        if (packetRegistred->getSlot() && packetRegistred->getSlotCall())
            (packetRegistred->getSlot()->*packetRegistred->getSlotCall())(false, packetRegistred);
        Protocol::unregisterPacket(packetRegistred);
    } else {
        SlotPacketMap::iterator it = _slotPacketMap.find(
                    static_cast<SlotType> (_extractedHeader->_slotType));
        if (it == _slotPacketMap.end())
        {
            LOG << "Packet with id = " << (int) _extractedHeader->_slotType << " is not handled" << std::endl;
            return ;
        }
        Packet *p = _packetFactory.generate();
        p->setNetwork(caller);
        p->setTimeout(0);
        p->setHeader(_extractedHeader);
        _slotPacketMap[
                static_cast<SlotType>(_extractedHeader->_slotType)
                ]->onCall(false, p);
        _packetFactory.invalidate(p);
    }
}

bool            Protocol::isValidPacket() const
{
    return (true);
}

void Protocol::onWrite(Network::Network *net)
{
    (void) net;
}

void Protocol::onDisconnect(Network::Network *net)
{
    (void) net;
}


Packet          *Protocol::getPacketFrom(Network::Network *net, unsigned int id)
{
    for (Protocol::IdPacketMap::iterator it = _packetMap.begin();
         it != _packetMap.end(); ++it) {
            if ((*it)->getNetwork() == net && (*it)->getHeader()._packetId == id)
                return (*it);
    }
    return (NULL);
}

} // !namespace: Protocol
