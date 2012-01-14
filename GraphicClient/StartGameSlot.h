#ifndef STARTGAMESLOT_H
#define STARTGAMESLOT_H

#include <QObject>
#include "Protocol.h"
#include "Packet.h"
#include "Singleton.h"
#include "SystemDefines.h"

class StartGameSlot : public QObject, public Protocol::NetworkSlot
{
    Q_OBJECT

signals:
    void    startGame();

public:
    StartGameSlot();
    virtual void onCall(bool isOnTimeout, Packet *packet, Protocol::Protocol *proto, void *data);
};

typedef Singleton<StartGameSlot>     StartGameSlotSingleton;

#endif // STARTGAMESLOT_H
