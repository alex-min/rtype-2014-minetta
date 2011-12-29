#ifndef SERVERCORE_H
#define SERVERCORE_H
#include "Pool.h"
#include "ServerGame.h"
#include "MyString.h"
#include "Protocol.h"
#include "MyNetworkManager.h"
#include "ConnectionSlot.h"
#include "LoginMapper.h"

class ServerCore
{
public:
    ServerCore();
    virtual ~ServerCore();
    void    start(UInt16 port);
    void    createGame(String const &gameName);
    Protocol::LoginMapper &getLoginMapper();

protected:
    PoolFactory< ServerGame >   _gamePool;
    Protocol::Protocol          _proto;
    Network::MyNetworkManager   _networkManager;
    Network::Network            *_net;
    Network::MySocket            _mainSock;
    Protocol::LoginMapper        _mapper;
};

#endif // SERVERCORE_H
