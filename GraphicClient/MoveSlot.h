#ifndef MOVESLOT_H
#define MOVESLOT_H

#include <QObject>
#include "Protocol.h"
#include "Packet.h"
#include "Singleton.h"
#include "SystemDefines.h"

class MoveSlot : public QObject, public Protocol::NetworkSlot
{
    Q_OBJECT

signals:
    void    posChanged(UInt16 id, UInt16 x, UInt16 y);

public:
    MoveSlot();
    void    sendNewPlayerPos(Protocol::Protocol *proto, Network::Network *net, float x, float y);
    virtual void onCall(bool isOnTimeout, Packet *packet, Protocol::Protocol *proto, void *data);
};

typedef Singleton<MoveSlot>     MoveSlotSingleton;

#endif // MOVESLOT_H
