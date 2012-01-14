#ifndef LISTGAMESLOT_H
#define LISTGAMESLOT_H

#include <QObject>
#include "Protocol.h"
#include "Packet.h"
#include "Singleton.h"
#include "SystemDefines.h"

class ListGameSlot : public QObject, public Protocol::NetworkSlot
{
    Q_OBJECT

signals:
    void    newGame(UInt8, UInt8, QString const &);

public:
    ListGameSlot();
    void requestGameList(Protocol::Protocol *proto, Network::Network *net);
    virtual void onCall(bool isOnTimeout, Packet *packet, Protocol::Protocol *proto, void *data);
};

typedef Singleton<ListGameSlot>     ListGameSlotSingleton;

#endif // LISTGAMESLOT_H
