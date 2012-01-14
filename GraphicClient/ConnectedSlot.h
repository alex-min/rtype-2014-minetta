#ifndef CONNECTEDSLOT_H
#define CONNECTEDSLOT_H

#include <QObject>
#include "Protocol.h"
#include "Packet.h"
#include "Singleton.h"

class ConnectedSlot : public QObject, public Protocol::NetworkSlot
{
    Q_OBJECT

signals:
    void connected(bool, short);

public:
    ConnectedSlot();
    void sendConnect(std::string const &login, Protocol::Protocol *proto, Network::Network *net);
    virtual void onCall(bool isOnTimeout, Packet *packet, Protocol::Protocol *proto, void *data);
};

typedef Singleton<ConnectedSlot>     ConnectedSlotSingleton;


#endif // CONNECTEDSLOT_H
