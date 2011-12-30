#ifndef MOVESLOT_H
#define MOVESLOT_H

#include <QObject>
#include "Protocol.h"
#include "Packet.h"
#include "Singleton.h"

class MoveSlot : public QObject, public Protocol::NetworkSlot
{
    Q_OBJECT

signals:
    void    posChanged();
public:
    MoveSlot();

    void    sendNewPlayerPos(Protocol::Protocol *proto, Network::Network *net, int playerId, float x, float y);
    virtual void onCall(bool isOnTimeout, Packet *packet, Protocol::Protocol *proto, void *data);
};

typedef Singleton<MoveSlot>     MoveSlotSingleton;

#endif // MOVESLOT_H
