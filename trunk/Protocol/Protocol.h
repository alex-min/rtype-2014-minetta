#ifndef PROTOCOL_H
#define PROTOCOL_H
#include "SystemDefines.h"

namespace Protocol {

enum {
     PACKET_CONTENT_SIZE = 64,
     DEFAULT_TIMEOUT = 5000
     };


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

class Protocol
{
public:
    Protocol();
};
} // !namespace : Protocol

#endif // PROTOCOL_H
