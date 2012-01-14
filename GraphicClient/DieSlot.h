#ifndef DIESLOT_H
#define DIESLOT_H

#include <QObject>
#include <QMetaType>
#include "Protocol.h"
#include "Packet.h"
#include "Singleton.h"
#include "SystemDefines.h"

class DieSlot : public QObject, public Protocol::NetworkSlot
{
    Q_OBJECT

signals:
    void    die(UInt16 id);

public:
    DieSlot();
    void    sendDie(Protocol::Protocol *proto, Network::Network *net);
    virtual void onCall(bool isOnTimeout, Packet *packet, Protocol::Protocol *proto, void *data);
};

typedef Singleton<DieSlot>     DieSlotSingleton;


#endif // DIESLOT_H
