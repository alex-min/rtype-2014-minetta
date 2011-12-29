#ifndef NETWORKSLOT_H
#define NETWORKSLOT_H
#include "SystemDefines.h"

class Packet;

namespace Protocol {

class Protocol;

class NetworkSlot {
public:
    enum {MAX_BUFFER_SIZE};
    virtual void onCall(bool isOnTimeout, Packet *packet, Protocol *, void *) {
        (void) isOnTimeout;
        (void) packet;
        LOGERR << " packet not handled, dropping..." << std::endl;
    }
protected:
    char        _tmpBuffer[MAX_BUFFER_SIZE];
};

typedef void (NetworkSlot::*SlotCall)(bool timeout, Packet *);

} // !namespace : Protocol

#endif // NETWORKSLOT_H
