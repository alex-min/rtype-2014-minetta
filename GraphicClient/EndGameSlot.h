#ifndef ENDGAMESLOT_H
#define ENDGAMESLOT_H

#include <QObject>
#include "Protocol.h"
#include "Packet.h"
#include "Singleton.h"
#include "SystemDefines.h"

class EndGameSlot : public QObject, public Protocol::NetworkSlot
{
    Q_OBJECT

signals:
    void endGame();

public:
    EndGameSlot();
    virtual void onCall(bool isOnTimeout, Packet *packet, Protocol::Protocol *proto, void *data);
};

typedef Singleton<EndGameSlot>     EndGameSlotSingleton;

#endif // ENDGAMESLOT_H
