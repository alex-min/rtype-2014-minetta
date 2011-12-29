#include "ServerCore.h"

ServerCore::ServerCore()
{
}

ServerCore::~ServerCore()
{

}

void    ServerCore::createGame(String const &gameName)
{
    ServerGame *game = _gamePool.generate();
    game->setName(gameName);
    game->run();
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
    _networkManager.addNetwork(net);
    _proto.registerSlotType(Protocol::CONNECT, new ConnectionSlot(), this);
    while (1) {
        _networkManager.run(300);
    }
}
