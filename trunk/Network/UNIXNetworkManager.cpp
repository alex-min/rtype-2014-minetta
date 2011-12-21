#include "UNIXNetworkManager.h"

UNIXNetworkManager::UNIXNetworkManager() :
    _maxfd(-1),
    _mainBuffer(new char[4096]),
    _slot(NULL)
{
}

void UNIXNetworkManager::addNetwork(Network::MySocket *sock)
{
    if (!sock || !(sock->isConnected()))
        return ;
    Network::Network *net = new Network::Network(sock);
    UNIXNetworkManager::addNetwork(net);
}

void UNIXNetworkManager::addNetwork(Network::Network *network)
{
    if (network && network->getSocket())
    {
        _network.push_back(network);
        if (network->getSocket()->UNIXGetSocket() > _maxfd)
        _maxfd = network->getSocket()->UNIXGetSocket();
     UNIXNetworkManager::generateReadFs();
    }
}

void UNIXNetworkManager::removeNetwork(Network::Network *network)
{
    _network.remove(network);
    network->getSocket()->disconnect();
}

void UNIXNetworkManager::generateReadFs()
{
    FD_ZERO(&_readfs);
    for (std::list<Network::Network *>::iterator it = _network.begin();
         it != _network.end(); ++it)
    {
        FD_SET((*it)->getSocket()->UNIXGetSocket(), &_readfs);
    }
}

void UNIXNetworkManager::generateWriteFs()
{
    _hasWriteFs = false;
    FD_ZERO(&_writefs);
    for (std::list<Network::Network *>::iterator it = _network.begin(); it != _network.end()
         ; ++it)
    {
        if (!((*it)->getWriteBuffer()->isEmpty()))
        {
            _hasWriteFs = true;
            FD_SET((*it)->getSocket()->UNIXGetSocket(), &_writefs);
        }
    }
}

Network::Network *UNIXNetworkManager::getUdpClient(Network::Network *remoteServer) {
    UInt64 checkIp = _udpReceivedIp.toInt();
    UInt64 checkPort = _udpReceivedPort;
    checkPort <<= 32;
    checkIp |= checkPort;
    std::map<UInt64, Network::Network *>::iterator it = _udpMapping.find(checkIp);
    if (it != _udpMapping.end()) {
            Network::Network *net = it->second;
            return (net);
    } else {
        Network::MySocket *sock = new Network::MySocket();
        sock->UDPConnectWithoutSocket(_udpReceivedIp, _udpReceivedPort);
        Network::Network  *client = new Network::Network(sock);
        UNIXNetworkManager::addNetwork(client);
        _udpMapping[checkIp] = client;
        if (_slot) _slot->onClientConnected(remoteServer, client);
        LOG << "New client connected from udp://" << _udpReceivedIp.toString() <<
            ":" << _udpReceivedPort << std::endl;
        return (0);
    }
}


void UNIXNetworkManager::udpServerReadEvent(Network::Network *net)
{
    (void) net;
    try {
        UInt16 byteRead = net->getSocket()->readFrom(&_udpReceivedIp, &_udpReceivedPort,
                                   _mainBuffer,
                                   EACH_READ_SIZE);

        UNIXNetworkManager::getUdpClient(net);
        if (_slot) _slot->onRead(net, net);
        net->getReadBuffer()->append(_mainBuffer, byteRead);
    } catch (NetworkDisconnect &) {
        if (_slot) _slot->onDisconnect(net);
    }
}

void UNIXNetworkManager::readEvent(Network::Network *net)
{
    LOG << "Read Event" << std::endl;
    if (!net)
        return ;
  if (!(net->getSocket()->isConnected()))
   {
        UNIXNetworkManager::removeNetwork(net);
        return ;
   }

    if (net->getSocket()->isServerSock())
    {
        if (net->getSocket()->getType() == Network::ISocket::TCP) {
            LOGERR << "tcp server not implemeted yet" << std::endl;
        } else {
            UNIXNetworkManager::udpServerReadEvent(net);
        }
    } else {
        LOGERR  << "Client read sock not implemented" << std::endl;
    }
}

void UNIXNetworkManager::writeEvent(Network::Network *net)
{
    (void) net;
    LOGERR << "not implemented" << std::endl;
}

void  UNIXNetworkManager::parseNetworkList()
{
    for (std::list<Network::Network *>::iterator it = _network.begin(); it != _network.end()
         ; ++it)
    {
        if ((*it)->getSocket() && (*it)->getSocket()->UNIXGetSocket() != SOCKET_ERROR &&
                FD_ISSET((*it)->getSocket()->UNIXGetSocket(), &_readfs))
            UNIXNetworkManager::readEvent(*it);
        else if ((*it)->getSocket() && (*it)->getSocket()->UNIXGetSocket() != SOCKET_ERROR
                 && FD_ISSET((*it)->getSocket()->UNIXGetSocket(), &_writefs))
            UNIXNetworkManager::writeEvent(*it);
    }
}

void UNIXNetworkManager::run(long msTimeout)
{
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = msTimeout  *1000;
    UNIXNetworkManager::generateWriteFs();

    UNIXNetworkManager::generateReadFs();
    libc::Memcpy(&_readfscpy, &_readfs, sizeof(fd_set));
    if (::select(_maxfd + 1, &_readfs, (_hasWriteFs == true) ? &_writefs : NULL, NULL,
                 (msTimeout == -1) ? NULL : &timeout) == -1)
    {
        return ;
    }
    UNIXNetworkManager::parseNetworkList();
}

void UNIXNetworkManager::setSlotListener(Network::NetworkManagerSlot *slot)
{
    _slot = slot;
}
