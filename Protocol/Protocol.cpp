#include "Protocol.h"
#include "Packet.h"
#include "CRC.h"

namespace Protocol {
Protocol::Protocol() :
    _mainBuffer(new char[MAX_READ_SIZE]),
    _packetCount(1)
{
    _callBackDisconnect = NULL;
    _ptr = NULL;
}

Protocol::~Protocol() {
    delete [] _mainBuffer;
}

LoginMapper &   Protocol::getLoginMapper()
{
    return (_mapper);
}

LoginMapper const &   Protocol::getLoginMapper() const
{
    return (_mapper);
}

void Protocol::onClientConnected(Network::Network *remote, Network::Network *client)
{
    (void) remote;
    (void) client;
}

void            Protocol::storePointer(void *ptr)
{
    _ptr = ptr;
}

void            *Protocol::getPointer() const
{
    return (_ptr);
}


void Protocol::onRead(Network::Network *remote, Network::Network *client)
{
    (void) remote;
    if (client->getReadBuffer()->getByteKeep() != HEADBYTE)
        client->getReadBuffer()->extractKeepDelim(_mainBuffer, MAX_READ_SIZE, HEADBYTE);
    if (client->getReadBuffer()->getReadSize() < sizeof(NetworkPacket::NetworkHeader))
    {
        return ;
    }

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
    Protocol::onRead(remote, client);
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

void            Protocol::registerSlotType(SlotType type, NetworkSlot *slot, void *object)
{
    _slotPacketMap[type] = std::pair< NetworkSlot *, void *> (slot, object);
}

void            Protocol::send(Network::Network *net, SlotType packetType,
                     const void *content, UInt16 len)
{
    _sendingHeader._begin = HEADBYTE;
    _sendingHeader._slotType = packetType;
    _sendingHeader._packetId = _packetCount;
    _sendingHeader._len = len;
//    _sendingHeader._checksum = 0x4242; // TODO : fix this
//    _sendingHeader._checksumData = 0x4242; // TODO : fix this
    // TODO : a verifier
    _sendingHeader._checksum = 0;
    _sendingHeader._checksumData = 0;
    _sendingHeader._checksum = CRC::getCRC16(&_sendingHeader, sizeof(NetworkPacket::NetworkHeader));
    _sendingHeader._checksumData = CRC::getCRC16(content, len);

    net->getWriteBuffer()->append(&_sendingHeader, sizeof(NetworkPacket::NetworkHeader));
    net->getWriteBuffer()->append(content, len);
    _packetCount++;
}

void            Protocol::send(Network::Network *net, SlotType packetType,
                     const void *content, UInt16 len, UInt16 packetId)
{
    _sendingHeader._begin = HEADBYTE;
    _sendingHeader._slotType = packetType;
    _sendingHeader._packetId = packetId;
    _sendingHeader._len = len;
//    _sendingHeader._checksum = 0x4242; // TODO : fix this
//    _sendingHeader._checksumData = 0x4242; // TODO : fix this
    // TODO : a verifier
    _sendingHeader._checksum = 0;
    _sendingHeader._checksumData = 0;
    _sendingHeader._checksum = CRC::getCRC16(&_sendingHeader, sizeof(NetworkPacket::NetworkHeader));
    _sendingHeader._checksumData = CRC::getCRC16(content, len);

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
        packetRegistred->setData(_mainBuffer + sizeof(NetworkPacket::NetworkHeader));
        if (packetRegistred->getSlot() && packetRegistred->getSlotCall())
            (packetRegistred->getSlot()->*packetRegistred->getSlotCall())(false, packetRegistred, this);
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
        p->setData(_mainBuffer + sizeof(NetworkPacket::NetworkHeader));
       std::pair< NetworkSlot *, void *> cur = _slotPacketMap[
               static_cast<SlotType>(_extractedHeader->_slotType)
               ];
        cur.first->onCall(false, p, this, cur.second);
        _packetFactory.invalidate(p);
    }
}

bool            Protocol::isValidPacket() const
{
    // TODO : a verifier
    NetworkPacket::NetworkHeader *header = reinterpret_cast<NetworkPacket::NetworkHeader *>(_mainBuffer);
    UInt16      checksumHead = header->_checksum;
    UInt16      checksumData = header->_checksumData;
    bool        ret = true;

    header->_checksum = 0;
    header->_checksumData = 0;
    header->_checksum = CRC::getCRC16(_mainBuffer, sizeof(NetworkPacket::NetworkHeader));
    header->_checksumData = CRC::getCRC16(_mainBuffer + sizeof(NetworkPacket::NetworkHeader), header->_len);

    if ((header->_checksum != checksumHead) || (header->_checksumData != checksumData))
        ret = false;

    header->_checksum = checksumHead;
    header->_checksumData = checksumData;
    return ret;

//    if (((NetworkPacket::NetworkHeader *) _mainBuffer)->_checksum != 0x4242)
//        return (false);
//    return (true);
}

void Protocol::onWrite(Network::Network *net)
{
    (void) net;
}

void Protocol::onDisconnect(Network::Network *net)
{
    if (net)
    {
        _mapper.removePlayer(_mapper.getByNetwork(net));
        if (_callBackDisconnect)
            (*_callBackDisconnect)(net, _sendData);
    }
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

String Protocol::getLoginFromData(const void *data, UInt16 len)
{
    String  ret;
    bool nullTerminated = false;

    for (unsigned int i = 0; i < len; i++) {
        if (static_cast<const char *> (data)[i] == 0)
            nullTerminated = true;
    }
    if (nullTerminated) {
    ret = std::string(static_cast<const char *> (data));
    return (ret);
    }
    return ("");
}

void    Protocol::setSendData(void *d)
{
    _sendData = d;
}

void    Protocol::setDisconnectCallback(callBackDisconnect fct)
{
    _callBackDisconnect = fct;
}

} // !namespace: Protocol
