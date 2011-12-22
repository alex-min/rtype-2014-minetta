#ifndef NETWORKSLOT_H
#define NETWORKSLOT_H

class Packet;

namespace Protocol {

class NetworkSlot {
    virtual void onCall(bool isOnTimeout, Packet *packet) = 0;
};

typedef void (NetworkSlot::*SlotCall)(bool timeout, Packet *);

} // !namespace : Protocol

#endif // NETWORKSLOT_H
