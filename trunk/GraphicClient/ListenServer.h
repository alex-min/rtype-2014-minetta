#ifndef LISTENSERVER_H
#define LISTENSERVER_H

#include "CQThread.h"
#include "Network.h"
#include "MyNetworkManager.h"
#include "Protocol.h"
#include "MoveSlot.h"
#include "ConnectedSlot.h"
#include "ListGameSlot.h"
#include "CreateGameSlot.h"
#include "RefGameSlot.h"
#include "PopSlot.h"
#include "StartGameSlot.h"
#include "DieSlot.h"
#include "EndGameSlot.h"

class ListenServer : public CQThread
{
    Q_OBJECT

signals:
    void    posChanged(UInt16 id,UInt16 x, UInt16 y);
    void    newGame(UInt8, UInt8, QString const &);
    void    connected(bool,short);
    void    gameCreation(bool);
    void    gameAccess(bool b);
    void    popMonster(UInt16 id, UInt8 monsterType, UInt16 x, UInt16 y, Int32 date);
    void    startGame();
    void    die(UInt16 id);
    void    endGame();

public:
    ListenServer();
    virtual void run();
    void    sendDead();
    void    sendConnectUdp(std::string const &login);
    void    sendConnect(std::string const &login);
    void    joinGame(std::string const &gameName);
    void    sendNewPlayerPos(float x, float y);
    void    createGame(std::string const &gameName, char mapId, char nbPlayers);
    void    requestGamesList();
    void    sendMissilPos(float x, float y);
    void    closeAllSocket();
    ~ListenServer();

public slots:
    void registerUdpSocket(bool b, UInt16 port);

private:
    Network::MyNetworkManager   _networkManager;
    Network::Network            *_net;
    Network::Network            *_udpNet;
    Protocol::Protocol          _proto;
    bool                        _connected;
    bool                        _udpConnected;
};

typedef Singleton<ListenServer>     ListenServerSingleton;

#endif // LISTENSERVER_H
