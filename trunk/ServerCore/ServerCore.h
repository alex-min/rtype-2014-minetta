#ifndef SERVERCORE_H
#define SERVERCORE_H
#include "Pool.h"
#include "ServerGame.h"
#include "MyString.h"
#include "Protocol.h"
#include "MyNetworkManager.h"
#include "LoginMapper.h"
#include "TimerPool.h"

#include "ConnectionSlot.h"
#include "MoveSlot.h"
#include "CreateGameSlot.h"
#include "ListGameSlot.h"
#include "JoinGameSlot.h"

class ServerCore
{
public:
    ServerCore();
    virtual         ~ServerCore();
    void            start(UInt16 port);
    ServerGame *    createGame(String const &gameName);

    void            removeGame(ServerGame *);

    ServerGame *                        getMapByName(String const &gameName) const;
    Protocol::LoginMapper &             getLoginMapper();

    PoolFactory< ServerGame > const &   getGamePool() const;

    Protocol::Protocol   *              getProtocol(); // cannot be const

protected:
    PoolFactory< ServerGame >   _gamePool;

    Protocol::Protocol                  _proto;
    Network::MyNetworkManager           _networkManager;
    Network::Network                    *_net;
    Network::MySocket                   _mainSock;
    Protocol::LoginMapper               _mapper;
    TimerPool<
    Packet *,
    Protocol::NetworkSlot,
    Protocol::SlotCall,
    Protocol::Protocol>                    _pool;
};

#endif // SERVERCORE_H
