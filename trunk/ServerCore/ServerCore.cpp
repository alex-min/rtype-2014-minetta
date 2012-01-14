#include "ServerCore.h"

ServerCore::ServerCore()
{
}

ServerCore::~ServerCore()
{

}

ServerGame *ServerCore::getMapByName(String const &gameName) const {
    PoolFactory<ServerGame>::ListType const &mapList =_gamePool.getMapList();
        for (PoolFactory<ServerGame>::ListType::const_iterator it = mapList.begin();
         it != mapList.end(); ++it) {
         if (it->second == false && it->first->getName() == gameName) {
            return (it->first);
        }
    }
    return (NULL);
}

ServerGame*    ServerCore::createGame(String const &gameName)
{
    LOG << "game->getName() => " << "LOL" << std::endl;
    ServerGame *gameFromName = ServerCore::getMapByName(gameName);
    if (gameFromName)
        return (NULL);
    ServerGame *game = _gamePool.generate<ServerCore *>(this);
    LOG << (void *) game << std::endl;
    game->setName(gameName);
    game->setServerCore(this);
    game->start();
    LOG << "game->getName() => " << game->getName() << std::endl;
    return (game);
}

Protocol::LoginMapper &ServerCore::getLoginMapper()
{
    return (_mapper);
}

void    ServerCore::start(UInt16 port)
{
    bool res = _mainSock.createTCPServerSocket(port);
    if (res == false)
        throw Exception("ServerCore: Cannot create tcp Socket");
    _net = new Network::Network(&_mainSock);
    _networkManager.setSlotListener(&_proto);
    _networkManager.addNetwork(_net);
    _proto.registerSlotType(Protocol::CONNECT, new ConnectionSlot(), this);
    _proto.registerSlotType(Protocol::CREATE_GAME, new CreateGameSlot(), this);
    _proto.registerSlotType(Protocol::MOVE, new MoveSlot(), this);
    _proto.registerSlotType(Protocol::LIST_GAME, new ListGameSlot(), this);
    _proto.registerSlotType(Protocol::JOIN_GAME, new JoinGameSlot(), this);

    while (1) {
        _networkManager.run(_pool.getMsNextCall(&_proto));
        _pool.autocall(&_proto);
    }
}

PoolFactory< ServerGame > const &   ServerCore::getGamePool() const
{
    return _gamePool;
}

void        onDisconnectCallback(Network::Network *n, void *c)
{
    if (!c || !n)
        return ;
    ServerCore *core = reinterpret_cast<ServerCore *>(c);
    core->getLoginMapper().removePlayer(core->getLoginMapper().getByNetwork(n));
}

