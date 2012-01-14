#ifndef JOINGAMESLOT_H
#define JOINGAMESLOT_H

#include <QObject>
#include "Protocol.h"
#include "Packet.h"
#include "Singleton.h"
#include "SystemDefines.h"

class RefGameSlot : public QObject, public Protocol::NetworkSlot
{
    Q_OBJECT

signals:
    void    gameAccess(bool b, UInt16 port);

public:
    RefGameSlot();
    void    joinGame(Protocol::Protocol *proto, Network::Network *net, std::string const &gameName);
    virtual void onCall(bool isOnTimeout, Packet *packet, Protocol::Protocol *proto, void *data);
};

typedef Singleton<RefGameSlot>     RefGameSlotSingleton;
#endif // JOINGAMESLOT_H
