#include "UNIXNetworkManager.h"
#ifdef OS_UNIX

UNIXNetworkManager::UNIXNetworkManager() :
    _maxfd(-1),
    _mainBuffer(new char[4096]),
    _slot(NULL)
{
}

bool UNIXNetworkManager::isAClientFrom(Network::Network *client,
                                       Network::Network *remote)
{
    if (remote && remote->getSocket() && remote->getSocket()->isConnected()
            && client->getRemoteNetwork() == remote) {
        return (true);
    }
    return (false);
}

void UNIXNetworkManager::addNetwork(Network::MySocket *sock)
{
    if (!sock || !(sock->isConnected()))
        return ;
    Network::Network *net = new Network::Network(sock);
    UNIXNetworkManager::addNetwork(net);
}

void UNIXNetworkManager::addNetworkFromInside(Network::MySocket *sock)
{
    if (!sock || !(sock->isConnected()))
        return ;
    Network::Network *net = new Network::Network(sock);
    UNIXNetworkManager::addNetworkFromInside(net);
}

void UNIXNetworkManager::addNetworkFromInside(Network::Network *network)
{
    _network.push_back(network);
    if (network->getSocket()->UNIXGetSocket() > _maxfd)
    _maxfd = network->getSocket()->UNIXGetSocket();
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
        if ((*it)->getSocket()->UNIXGetSocket() != SOCKET_ERROR)
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
            if ((*it)->getSocket()->getType() == Network::ISocket::UDP &&
                    (*it)->getRemoteNetwork() &&
                    (*it)->getRemoteNetwork()->getSocket()
               )
            {
                FD_SET((*it)->getRemoteNetwork()->getSocket()->UNIXGetSocket(), &_writefs);
            }
            else if ((*it)->getSocket()->UNIXGetSocket() != SOCKET_ERROR)
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
            // TODO : Delete this line
            net->getWriteBuffer()->append("hello world", 11);
            return (net);
    } else {
        Network::MySocket *sock = new Network::MySocket();
        sock->UDPConnectWithoutSocket(_udpReceivedIp, _udpReceivedPort,
                                      remoteServer->getSocket());
        Network::Network  *client = new Network::Network(sock);
        client->setRemoteNetwork(remoteServer);
        UNIXNetworkManager::addNetworkFromInside(client);
        _udpMapping[checkIp] = client;
        if (_slot) _slot->onClientConnected(remoteServer, client);
        LOG << "New client connected from udp://" << client->getSocket()->getRemoteIp() <<
            ":" << client->getSocket()->getRemotePort() << std::endl;
        // TODO : Delete this line
        client->getWriteBuffer()->append("hello world", 11);
        return (0);
    }
}

void UNIXNetworkManager::tcpServerReadEvent(Network::Network *net)
{
    if (!net)
        return ;
    if (!(net->getSocket()->isConnected()))
    {
        UNIXNetworkManager::removeNetwork(net);
        return ;
    }
    try {
        Network::MySocket *sock = net->getSocket()->waitForClient();
        Network::Network  *client = new Network::Network(sock);
        client->setRemoteNetwork(net);
        UNIXNetworkManager::addNetwork(client);
        LOG << "New client connected from tcp://" << client->getSocket()->getRemoteIp() <<
            ":" << client->getSocket()->getRemotePort() << std::endl;
    } catch (NetworkDisconnect &) {
        LOGERR << "Server disconnected from tcp://" << net->getSocket()->getRemoteIp() <<
            ":" << net->getSocket()->getRemotePort() << std::endl;
        if (_slot) _slot->onDisconnect(net);
        UNIXNetworkManager::removeNetwork(net);
    }
}

void UNIXNetworkManager::tcpClientReadEvent(Network::Network *net)
{
    try {
    UInt16 readBytes = net->getSocket()->read(_mainBuffer, EACH_READ_SIZE);
    net->getReadBuffer()->append(_mainBuffer, readBytes);
    LOG << " ReadEvent (" << readBytes << " bytes read)" << std::endl;
     if (_slot) _slot->onRead(net->getRemoteNetwork(), net);
    } catch (NetworkDisconnect &) {
        LOGERR << "Client disconnected from tcp://" << net->getSocket()->getRemoteIp() <<
            ":" << net->getSocket()->getRemotePort() << std::endl;
        if (_slot) _slot->onDisconnect(net);
        UNIXNetworkManager::removeNetwork(net);
        throw;
    }
}

void UNIXNetworkManager::udpClientWriteEvent(Network::Network *net)
{
    if (!net || !(net->getSocket()) || !(net->getSocket()->isConnected()))
        return ;
    try {
        UInt32 sizeToWrite = net->getWriteBuffer()->extractKeep(_mainBuffer, EACH_READ_SIZE);
        LOG << "Sending (" << (int) sizeToWrite << " bytes)" << std::endl;
        UInt16 byteWritten = net->getSocket()->send(_mainBuffer, sizeToWrite);
        net->getWriteBuffer()->drop(byteWritten);

    } catch (NetworkDisconnect &) {
        LOGERR << "Client disconnected from udp://" << net->getSocket()->getRemoteIp() <<
            ":" << net->getSocket()->getRemotePort() << std::endl;
        if (_slot) _slot->onDisconnect(net);
        UNIXNetworkManager::removeNetwork(net);
        throw;
    }
}

void UNIXNetworkManager::udpServerReadEvent(Network::Network *net)
{

    try {
        UInt16 byteRead = net->getSocket()->readFrom(&_udpReceivedIp, &_udpReceivedPort,
                                   _mainBuffer,
                                   EACH_READ_SIZE);

        UNIXNetworkManager::getUdpClient(net);
        LOG << " ReadEvent (" << byteRead << " bytes read)" << std::endl;
        if (_slot) _slot->onRead(net, net);
        net->getReadBuffer()->append(_mainBuffer, byteRead);
    } catch (NetworkDisconnect &) {
        if (_slot) _slot->onDisconnect(net);
        UNIXNetworkManager::removeNetwork(net);
        throw;
    }
}

void UNIXNetworkManager::readEvent(Network::Network *net)
{
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
            UNIXNetworkManager::tcpServerReadEvent(net);
        } else {
            UNIXNetworkManager::udpServerReadEvent(net);
        }
    } else {
         if (net->getSocket()->getType() == Network::ISocket::TCP) {
            UNIXNetworkManager::tcpClientReadEvent(net);
         } else {
            // Cannot exist
         }
    }
}

void UNIXNetworkManager::writeEvent(Network::Network *net)
{
    (void) net;
    if (!net)
         return ;
    if (net->getSocket()->getType() == Network::ISocket::TCP) {
        UInt32 sizeToWrite = net->getWriteBuffer()->extractKeep(_mainBuffer, EACH_READ_SIZE);
        UInt16 byteWritten = net->getSocket()->send(_mainBuffer, sizeToWrite);
        net->getWriteBuffer()->drop(byteWritten);
    } else {
        if (net->getSocket()->isServerSock()) {
            for (std::list<Network::Network *>::iterator it = _network.begin();
                 it != _network.end(); ++it) {
                    if (UNIXNetworkManager::isAClientFrom(*it, net)) {
                        if ((*it)->getWriteBuffer()->getReadSize() > 0) {
                            UNIXNetworkManager::udpClientWriteEvent(*it);
                        }
                    }
            }
        } else {
            // cannot happen
        }
    }
}

void  UNIXNetworkManager::parseNetworkList()
{
    while (1)
    {
        try {
        for (std::list<Network::Network *>::iterator it = _network.begin(); it != _network.end()
             ; ++it)
        {
            if ((*it)->getSocket() && (*it)->getSocket()->UNIXGetSocket() != SOCKET_ERROR &&
                    FD_ISSET((*it)->getSocket()->UNIXGetSocket(), &_readfs))
            {
                UNIXNetworkManager::readEvent(*it);
                FD_CLR((*it)->getSocket()->UNIXGetSocket(), &_readfs);
                break;
            }
            else if ((*it)->getSocket() && (*it)->getSocket()->UNIXGetSocket() != SOCKET_ERROR
                     && FD_ISSET((*it)->getSocket()->UNIXGetSocket(), &_writefs))
            {
                UNIXNetworkManager::writeEvent(*it);
                FD_CLR((*it)->getSocket()->UNIXGetSocket(), &_readfs);
                break;
            }
        }
        return ;
        } catch (...) {}
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
#endif
