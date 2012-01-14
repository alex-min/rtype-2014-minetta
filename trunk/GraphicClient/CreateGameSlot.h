#ifndef CREATEGAMESLOT_H
#define CREATEGAMESLOT_H

#include <QObject>
#include "Protocol.h"
#include "Packet.h"
#include "Singleton.h"
#include "SystemDefines.h"

class CreateGameSlot: public QObject, public Protocol::NetworkSlot
{
    Q_OBJECT

signals:
    void    gameCreation(bool);

public:
    CreateGameSlot();
    void    createGame(Protocol::Protocol *proto, Network::Network *net, std::string const &gameName, char mapId, char nbPlayers);
    virtual void onCall(bool isOnTimeout, Packet *packet, Protocol::Protocol *proto, void *data);
};

typedef Singleton<CreateGameSlot>   CreateGameSlotSingleton;

#endif // CREATEGAMESLOT_H
