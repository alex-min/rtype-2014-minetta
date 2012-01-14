#ifndef POPSLOT_H
#define POPSLOT_H

#include <QObject>
#include "Protocol.h"
#include "Packet.h"
#include "Singleton.h"
#include "SystemDefines.h"

class PopSlot : public QObject, public Protocol::NetworkSlot
{
    Q_OBJECT

signals:
    void popMonster(UInt16 id, UInt8 monsterType, UInt16 x, UInt16 y, Int32 date);

public:
    PopSlot();
    virtual void onCall(bool isOnTimeout, Packet *packet, Protocol::Protocol *proto, void *data);
};

typedef Singleton<PopSlot>     PopSlotSingleton;

#endif // POPSLOT_H
