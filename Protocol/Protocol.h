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
    JOIN_GAME, REF_GAME, LIST_GAME, LEAVE_GAME, END_GAME, STATUS,
    DEAD, MOVE, POP, PING, PONG, START_GAME,
    UNKNOWN
};

enum eStatusReceived {VALID, INVALID, INCOMPLETE};
enum StatusId {OK, FAILED, USED, GAME_FULL, COMPLETE, GAME_OVER};

    struct NetworkPacket
    {
        struct NetworkHeader
        {
            UInt8       _begin;
            UInt8       _slotType;
            UInt16      _packetId;
            UInt16      _len;
            UInt16      _checksum;
            UInt16      _checksumData;
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
    LoginMapper const &getLoginMapper() const;
    void            unregisterPacket(Packet *);
    void            registerSlotType(SlotType type, NetworkSlot *slot, void *object = NULL);
    void            registerNextPacket(Network::Network *net, NetworkSlot *slot, SlotCall call,
                                       UInt16 timeout = DEFAULT_TIMEOUT);


public: // functions below are for special purpose only
    Packet          *getPacketFrom(Network::Network *net, unsigned int id);
    void            send(Network::Network *net, SlotType packetType,
                         const void *content, UInt16 len);
    void            send(Network::Network *net, SlotType packetType,
                         const void *content, UInt16 len, UInt16 packetId);

    void            storePointer(void *ptr);
    void            *getPointer() const;


    static      String getLoginFromData(const void *, UInt16 len);
    void        setSendData(void *);

    typedef     void    (*callBackDisconnect)(Network::Network *, void *);

    void        setDisconnectCallback(callBackDisconnect);

protected:
    void                            *_ptr;
    char *                          _mainBuffer;
    int                             _packetCount;
    NetworkPacket::NetworkHeader *  _extractedHeader;
    NetworkPacket::NetworkHeader    _sendingHeader;
    LoginMapper                     _mapper;
    IdPacketMap                     _packetMap;
    SlotPacketMap                   _slotPacketMap;
    PoolFactory<Packet>             _packetFactory;

    void                            *_sendData;
    callBackDisconnect              _callBackDisconnect;

};
} // !namespace : Protocol

#endif // PROTOCOL_H
