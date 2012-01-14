#include "ServerGame.h"
#include "ITime.h"
#include "MoveSlot.h"
#include "PopSlot.h"
#include "DeadSlot.h"
#ifdef OS_WINDOWS
#include <windows.h>
#define random(u) rand(u)
#endif

void        onDisconnectCallback(Network::Network *n, void *c);

ServerGame::ServerGame() :
    _name("_DEFAULT_GAME_NAME"),
    _core(NULL),
    _mapId(0),
    _maxNbPlayer(0)
{
    _serverCore = NULL;
    _proto.setDisconnectCallback(&onDisconnectCallback);
    _popSlot = new PopSlot();
}

ServerGame::ServerGame(ServerCore *core)
    : _monsterId(0),
      _name("_DEFAULT_GAME_NAME"),
      _core(core),
      _mapId(0),
      _maxNbPlayer(0)
{
    _serverCore = NULL;
    _proto.setSendData(_core);
    _proto.setDisconnectCallback(&onDisconnectCallback);
    _popSlot = new PopSlot();

}

void    ServerGame::setServerCore(ServerCore *c)
{
    _serverCore = c;
}

UInt32  ServerGame::getGamePort() const
{
   return (_gamePort);
}

void    ServerGame::setName(String const & name)
{
    _name = name;
}

void    ServerGame::generateGameName()
{
    _name = "_DEFAULT_GAME_NAME";
    MyTime t;
    t.setToMsTimeOfDay();
    _name += String(t.getMs());
}

Network::Network    const * ServerGame::getNetwork() const
{
    return _net;
}

UInt16  ServerGame::generateId()
{
   ++_monsterId;
    return (_monsterId);
}

void    ServerGame::generateMonster()
{
    static unsigned int i = 0;

    Protocol::LoginMapper::MapperType const &mapper = ServerGame::getMapperList();

  // LOG << "miam : " << mapper.size() << std::endl;
    if (i % 10 == 0)
            {
                UInt32 y = random() % 600 + 10;
        for (Protocol::LoginMapper::MapperType::const_iterator it2 = mapper.begin();
             it2 != mapper.end(); ++it2) {
                 _popSlot->sendPop(&_proto, (*it2)->getNetwork(),
                                          generateId(), 1, 800, y,
                                          0);

        }

    }
    ++i;
    return ;
    if (i % 30 == 0) {
        ServerMonster *m = _monsterPool.generate();
        m->setPopDelay(5000);
        m->setId(generateId());
    }

    ++i;
    if (i % 10 == 0) {
    PoolFactory< ServerMonster >::ListType &map = _monsterPool.getMapList();
    for (std::map< ServerMonster *, bool >::iterator it = map.begin();
    it != map.end(); ++it) {
        if (it->second == false)
        {
            if (it->first && it->first->getPopDelay()) {
                Protocol::LoginMapper::MapperType const &mapper = ServerGame::getMapperList();
                for (Protocol::LoginMapper::MapperType::const_iterator it2 = mapper.begin();
                     it2 != mapper.end(); ++it2) {
                    _popSlot->sendPop(&_proto, (*it2)->getNetwork(),
                                      it->first->getId(), 1, 0, 0,
                                      it->first->getPopDelay());
                }
            }

        } else {
                   _monsterPool.invalidate(it->first);
               }
    }

    }
}

void    ServerGame::sendStartGame()
{
    Protocol::LoginMapper::MapperType const &mapper = ServerGame::getMapperList();
    for (Protocol::LoginMapper::MapperType::const_iterator it2 = mapper.begin();
         it2 != mapper.end(); ++it2) {
        LOGERR << "Network pointer : " << (*it2)->getNetwork() << std::endl;
        _proto.send((*it2)->getNetwork(), Protocol::START_GAME,
                    "h", 1, -1);
    }
}

void    ServerGame::run()
{
    _gamePort = 1337 + random() % 800;
    LOGERR << "GamePort " << _gamePort << std::endl;
    bool res = _mainSock.createUDPServerSocket(_gamePort);
    if (res == false)
        throw Exception("ServerCore: Cannot create tcp Socket");
    _proto.registerSlotType(Protocol::MOVE, new MoveSlot(), _serverCore);
    _proto.registerSlotType(Protocol::POP, _popSlot, _serverCore);
    _proto.registerSlotType(Protocol::CONNECT, new ConnectionSlot(), _serverCore);
    _proto.registerSlotType(Protocol::DEAD, new DeadSlot(), _serverCore);
    _proto.storePointer(this);
    _net = new Network::Network(&_mainSock);
    _networkManager.setSlotListener(&_proto);
    _networkManager.addNetwork(_net);
    while (1) {
        _networkManager.run(_pool.getMsNextCall(&_proto));
        _pool.autocall(&_proto);
        if (ServerGame::getMapperList().size() < ServerGame::getMaxNbPlayer()) {
          //  LOG << "Waiting more player ... (" << (int) ServerGame::getMaxNbPlayer() << ")" << std::endl;
        } else {
            generateMonster();
        }
    }
}

String const &    ServerGame::getName() const
{
    return (_name);
}

void        ServerGame::setMapId(UInt8 id)
{
    _mapId = id;
}

void        ServerGame::setMaxNbPlayer(UInt8 nb)
{
    _maxNbPlayer = nb;
}

UInt8       ServerGame::getMapId() const
{
    return _mapId;
}

UInt8       ServerGame::getMaxNbPlayer() const
{
    return _maxNbPlayer;
}

void    ServerGame::erase()
{
    // TODO : restart thread and start everything
}

void    ServerGame::erase(ServerCore *)
{
    // TODO : restart thread and start everything
}

void    ServerGame::invalidateEvent()
{
    // TODO : kill evrything and pause thread
}

Protocol::Protocol  const &ServerGame::getProtocol() const
{
    return _proto;
}

Protocol::LoginMapper::MapperType const &ServerGame::getMapperList() const
{
    return _proto.getLoginMapper().getMapperList();
}

Protocol::LoginMapper::MapperType &ServerGame::getMapperList()
{
    return _proto.getLoginMapper().getMapperList();
}

Protocol::LoginMapper & ServerGame::getMapper()
{
    return (_proto.getLoginMapper());
}
