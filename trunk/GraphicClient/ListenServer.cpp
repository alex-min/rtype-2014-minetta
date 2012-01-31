#include "ListenServer.h"
#include <QMetaType>

ListenServer::ListenServer()
{
//    Network::MySocket *sock = new Network::MySocket;

//    _net = 0;
//    _udpNet = 0;
//    _udpConnected = false;
//    _connected = sock->connect("127.0.0.1", 5050);
//    sock->setRemoteIp("127.0.0.1");

//    _net = new Network::Network(sock);

//    _proto.registerSlotType(Protocol::CONNECTED, ConnectedSlotSingleton::getInstance(), this);
//    _proto.registerSlotType(Protocol::MOVE, MoveSlotSingleton::getInstance(), this);
//    _proto.registerSlotType(Protocol::LIST_GAME, ListGameSlotSingleton::getInstance(), this);
//    _proto.registerSlotType(Protocol::CREATE_GAME, CreateGameSlotSingleton::getInstance(), this);
//    _proto.registerSlotType(Protocol::REF_GAME, RefGameSlotSingleton::getInstance(), this);
//    _proto.registerSlotType(Protocol::POP, PopSlotSingleton::getInstance(), this);
//    _proto.registerSlotType(Protocol::START_GAME, StartGameSlotSingleton::getInstance(), this);
//    _proto.registerSlotType(Protocol::DEAD, DieSlotSingleton::getInstance(), this);
//    _proto.registerSlotType(Protocol::END_GAME, EndGameSlotSingleton::getInstance(), this);

//    _networkManager.setSlotListener(&_proto);
//    _networkManager.addNetwork(_net);

//    qRegisterMetaType<UInt16>("UInt16");
//    qRegisterMetaType<UInt8>("UInt8");
//    qRegisterMetaType<Int32>("Int32");
//    qRegisterMetaType<Packet>("Packet");

//    connect(MoveSlotSingleton::getInstance(), SIGNAL(posChanged(UInt16,UInt16,UInt16)), this, SIGNAL(posChanged(UInt16,UInt16,UInt16)));
//    connect(ListGameSlotSingleton::getInstance(), SIGNAL(newGame(UInt8,UInt8,QString)), this, SIGNAL(newGame(UInt8,UInt8,QString)));
//    connect(ConnectedSlotSingleton::getInstance(), SIGNAL(connected(bool,short)), this, SIGNAL(connected(bool,short)));
//    connect(CreateGameSlotSingleton::getInstance(), SIGNAL(gameCreation(bool)), this, SIGNAL(gameCreation(bool)));
//    connect(RefGameSlotSingleton::getInstance(), SIGNAL(gameAccess(bool,UInt16)), this, SLOT(registerUdpSocket(bool,UInt16)));
//    connect(PopSlotSingleton::getInstance(), SIGNAL(popMonster(UInt16,UInt8,UInt16,UInt16,Int32)), SIGNAL(popMonster(UInt16,UInt8,UInt16,UInt16,Int32)));
//    connect(StartGameSlotSingleton::getInstance(), SIGNAL(startGame()), SIGNAL(startGame()));
//    connect(DieSlotSingleton::getInstance(), SIGNAL(die(UInt16)), SIGNAL(die(UInt16)));
//    connect(EndGameSlotSingleton::getInstance(), SIGNAL(endGame()), SIGNAL(endGame()));
}

void ListenServer::init(const char *ip)
{
    Network::MySocket *sock = new Network::MySocket;

    _net = 0;
    _udpNet = 0;
    _udpConnected = false;
    _connected = sock->connect(ip, 5050);
    sock->setRemoteIp(ip);

    _net = new Network::Network(sock);

    _proto.registerSlotType(Protocol::CONNECTED, ConnectedSlotSingleton::getInstance(), this);
    _proto.registerSlotType(Protocol::MOVE, MoveSlotSingleton::getInstance(), this);
    _proto.registerSlotType(Protocol::LIST_GAME, ListGameSlotSingleton::getInstance(), this);
    _proto.registerSlotType(Protocol::CREATE_GAME, CreateGameSlotSingleton::getInstance(), this);
    _proto.registerSlotType(Protocol::REF_GAME, RefGameSlotSingleton::getInstance(), this);
    _proto.registerSlotType(Protocol::POP, PopSlotSingleton::getInstance(), this);
    _proto.registerSlotType(Protocol::START_GAME, StartGameSlotSingleton::getInstance(), this);
    _proto.registerSlotType(Protocol::DEAD, DieSlotSingleton::getInstance(), this);
    _proto.registerSlotType(Protocol::END_GAME, EndGameSlotSingleton::getInstance(), this);

    _networkManager.setSlotListener(&_proto);
    _networkManager.addNetwork(_net);

    qRegisterMetaType<UInt16>("UInt16");
    qRegisterMetaType<UInt8>("UInt8");
    qRegisterMetaType<Int32>("Int32");
    qRegisterMetaType<Packet>("Packet");

    connect(MoveSlotSingleton::getInstance(), SIGNAL(posChanged(UInt16,UInt16,UInt16)), this, SIGNAL(posChanged(UInt16,UInt16,UInt16)));
    connect(ListGameSlotSingleton::getInstance(), SIGNAL(newGame(UInt8,UInt8,QString)), this, SIGNAL(newGame(UInt8,UInt8,QString)));
    connect(ConnectedSlotSingleton::getInstance(), SIGNAL(connected(bool,short)), this, SIGNAL(connected(bool,short)));
    connect(CreateGameSlotSingleton::getInstance(), SIGNAL(gameCreation(bool)), this, SIGNAL(gameCreation(bool)));
    connect(RefGameSlotSingleton::getInstance(), SIGNAL(gameAccess(bool,UInt16)), this, SLOT(registerUdpSocket(bool,UInt16)));
    connect(PopSlotSingleton::getInstance(), SIGNAL(popMonster(UInt16,UInt8,UInt16,UInt16,Int32)), SIGNAL(popMonster(UInt16,UInt8,UInt16,UInt16,Int32)));
    connect(StartGameSlotSingleton::getInstance(), SIGNAL(startGame()), SIGNAL(startGame()));
    connect(DieSlotSingleton::getInstance(), SIGNAL(die(UInt16)), SIGNAL(die(UInt16)));
    connect(EndGameSlotSingleton::getInstance(), SIGNAL(endGame()), SIGNAL(endGame()));
}

void ListenServer::registerUdpSocket(bool b, UInt16 port)
{
    if (b)
    {

        Network::MySocket *udpSocket = new Network::MySocket;


        _udpConnected = udpSocket->connect(_net->getSocket()->getRemoteIp(), port, Network::ISocket::UDP);
        _udpNet = new Network::Network(udpSocket);
        _networkManager.addNetwork(_udpNet);
    }

    emit gameAccess(b);
}

void ListenServer::run()
{
    while (1)
    {
        _networkManager.run(300);
    }
}

void    ListenServer::sendDead()
{
    if (_udpConnected)
        DieSlotSingleton::getInstance()->sendDie(&_proto, _udpNet);
}

void    ListenServer::closeAllSocket()
{
    if (_net)
        _net->getSocket()->disconnect();
    if (_udpNet)
        _udpNet->getSocket()->disconnect();
}

void    ListenServer::sendMissilPos(float x, float y)
{
    if (_udpConnected)
    {
        static char buf[20];

        UInt16 posX = static_cast<int>(x);
        UInt16 posY = static_cast<int>(y);

        unsigned int tmpLen = 0;

        libc::Memadd(buf, &posX, sizeof(UInt16), tmpLen);
        libc::Memadd(buf, &posY, sizeof(UInt16), tmpLen);

        _proto.send(_udpNet, Protocol::POP, buf, tmpLen);
    }
}

void    ListenServer::joinGame(std::string const &gameName)
{
    if (_connected)
        RefGameSlotSingleton::getInstance()->joinGame(&_proto, _net, gameName);
}

void    ListenServer::createGame(std::string const &gameName, char mapId, char nbPlayers)
{
    if (_connected)
        CreateGameSlotSingleton::getInstance()->createGame(&_proto, _net, gameName, mapId, nbPlayers);
}

void    ListenServer::sendConnect(std::string const &login)
{
    if (_connected)
        ConnectedSlotSingleton::getInstance()->sendConnect(login, &_proto, _net);
}

void    ListenServer::sendConnectUdp(std::string const &login)
{
    if (_udpConnected)
        ConnectedSlotSingleton::getInstance()->sendConnect(login, &_proto, _udpNet);
}

void    ListenServer::sendNewPlayerPos(float x, float y)
{
    if (_udpConnected)
        MoveSlotSingleton::getInstance()->sendNewPlayerPos(&_proto, _udpNet, x, y);
}

void    ListenServer::requestGamesList()
{
    if (_connected)
        ListGameSlotSingleton::getInstance()->requestGameList(&_proto, _net);
}

ListenServer::~ListenServer()
{

}
