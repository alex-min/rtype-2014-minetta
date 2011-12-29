#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <list>
#include "SystemDefines.h"
#include "NetworkSlot.h"
#include "NetworkManagerSlot.h"
#include "LoginMapper.h"
#include "Pool.h"

namespace Protocol {

enum {
     PACKET_CONTENT_SIZE = 64,
     DEFAULT_TIMEOUT = 5000,
     MAX_READ_SIZE = 4096,
     HEADBYTE = 0x7
     };

enum SlotType {
    CONNECT, DISCONNECT, CONNECTED, CREATE_GAME,
    JOIN_GAME, LIST_GAME, LEAVE_GAME, END_GAME, STATUS,
    DEAD, MOVE, POP, PING, PONG,
    UNKNOWN
};

enum eStatusReceived {VALID, INVALID, INCOMPLETE};
enum StatusId {OK, FAILED, USED, GAME_FULL, COMPLETE, GAME_OVER};

    struct NetworkPacket
    {
        struct NetworkHeader
        {
            unsigned char _begin;
            unsigned char _slotType;
            unsigned short _packetId;
            unsigned short _len;
            unsigned short _checksum;
            unsigned short _checksumData;
        } PACKED;
        Byte        _packetContent[PACKET_CONTENT_SIZE];
    } PACKED;
class Protocol : public Network::NetworkManagerSlot
{
public:
    typedef std::list<Packet *> IdPacketMap;
    typedef std::map<SlotType, std::pair< NetworkSlot *, void *> > SlotPacketMap;

    Protocol();
    ~Protocol();
    virtual void    onClientConnected(Network::Network *remote, Network::Network *client);
    virtual void    onRead(Network::Network *remote, Network::Network *client);
    virtual void    onWrite(Network::Network *net);
    virtual void    onDisconnect(Network::Network *net);
    bool            isValidPacket() const;
    void            dispatchPacket(Network::Network *caller);
    LoginMapper &   getLoginMapper(); // cannot be const
    void            unregisterPacket(Packet *);
    void            registerSlotType(SlotType type, NetworkSlot *slot, void *object = NULL);
    void            registerNextPacket(Network::Network *net, NetworkSlot *slot, SlotCall call,
                                       UInt16 timeout = DEFAULT_TIMEOUT);

public: // functions below are for special purpose only
    Packet          *getPacketFrom(Network::Network *net, unsigned int id);
    void            send(Network::Network *net, SlotType packetType,
                         const void *content, UInt16 len);

    static      String getLoginFromData(const void *, UInt16 len);

protected:
    char *                          _mainBuffer;
    int                             _packetCount;
    NetworkPacket::NetworkHeader *  _extractedHeader;
    NetworkPacket::NetworkHeader    _sendingHeader;
    LoginMapper                     _mapper;
    IdPacketMap                     _packetMap;
    SlotPacketMap                   _slotPacketMap;
    PoolFactory<Packet>             _packetFactory;

};
} // !namespace : Protocol

#endif // PROTOCOL_H
