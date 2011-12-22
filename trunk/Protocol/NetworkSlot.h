#ifndef NETWORKSLOT_H
#define NETWORKSLOT_H
#include "SystemDefines.h"

class Packet;

namespace Protocol {

class Protocol;

class NetworkSlot {
public:
    virtual void onCall(bool isOnTimeout, Packet *packet, Protocol *) {
        (void) isOnTimeout;
        (void) packet;
        LOGERR << " packet not handled, dropping..." << std::endl;
    }
};

typedef void (NetworkSlot::*SlotCall)(bool timeout, Packet *);

} // !namespace : Protocol

#endif // NETWORKSLOT_H
