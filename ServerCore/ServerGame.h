#ifndef SERVERGAME_H
#define SERVERGAME_H
#include "Thread.h"
#include "MyString.h"
#include "MySleep.h"
#include "Protocol.h"
#include "MyNetworkManager.h"
#include "TimerPool.h"
#include "MonsterGenerator.h"
#include "ServerMonster.h"


class PopSlot;
class ServerCore;

class ServerGame : public Thread
{
public:
    ServerGame();
    ServerGame(ServerCore *core);
    void    setName(String const &);
    String const &      getName() const;

    void        setMapId(UInt8);
    void        setMaxNbPlayer(UInt8);
    UInt8       getMapId() const;
    UInt8       getMaxNbPlayer() const;

    Network::Network    const *getNetwork() const;
    void    generateGameName();
    virtual void run() {run(true);}
    virtual void run(bool loop);
//pool methods
    void    erase();
    void    erase(ServerCore *);
    void    invalidateEvent();
    void    generateMonster();
    UInt16  generateId();
    Protocol::Protocol  const &getProtocol() const;
    Protocol::LoginMapper::MapperType const &getMapperList() const;
    Protocol::LoginMapper::MapperType &getMapperList();
    Protocol::LoginMapper & getMapper();  // cannot be const
    UInt32  getGamePort() const;
    void    setServerCore(ServerCore *);
    void    sendStartGame();

protected:
    ServerCore                 *_serverCore;
    UInt32                    _gamePort;
    UInt16                    _monsterId;
    String                    _name;
    ServerCore                *_core;
    UInt8                       _mapId;
    UInt8                       _maxNbPlayer;
    Protocol::Protocol        _proto;
    Network::MyNetworkManager   _networkManager;
    Network::Network            *_net;
    Network::MySocket                   _mainSock;
    TimerPool<
    Packet *,
    Protocol::NetworkSlot,
    Protocol::SlotCall,
    Protocol::Protocol>                    _pool;
    PopSlot     *_popSlot;
    PoolFactory < ServerMonster >   _monsterPool;
};

#endif // SERVERGAME_H
