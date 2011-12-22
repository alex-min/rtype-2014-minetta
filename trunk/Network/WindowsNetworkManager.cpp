#include "WindowsNetworkManager.h"
#ifdef OS_WINDOWS

WindowsNetworkManager::WindowsNetworkManager() :
    _maxfd(-1),
    _mainBuffer(new char[4096]),
    _slot(NULL)
{
}

bool WindowsNetworkManager::isAClientFrom(Network::Network *client,
                                       Network::Network *remote)
{
    if (remote && remote->getSocket() && remote->getSocket()->isConnected()
            && client->getRemoteNetwork() == remote) {
        return (true);
    }
    return (false);
}

void WindowsNetworkManager::addNetwork(Network::MySocket *sock)
{
    if (!sock || !(sock->isConnected()))
        return ;
    Network::Network *net = new Network::Network(sock);
    WindowsNetworkManager::addNetwork(net);
}

void WindowsNetworkManager::addNetworkFromInside(Network::MySocket *sock)
{
    if (!sock || !(sock->isConnected()))
        return ;
    Network::Network *net = new Network::Network(sock);
    WindowsNetworkManager::addNetworkFromInside(net);
}

void WindowsNetworkManager::addNetworkFromInside(Network::Network *network)
{
    _network.push_back(network);
    if (network->getSocket()->WindowsGetSocket() > _maxfd)
    _maxfd = network->getSocket()->WindowsGetSocket();
}

void WindowsNetworkManager::addNetwork(Network::Network *network)
{
    if (network && network->getSocket())
    {
        _network.push_back(network);
        if (network->getSocket()->WindowsGetSocket() > _maxfd)
        _maxfd = network->getSocket()->WindowsGetSocket();
     WindowsNetworkManager::generateReadFs();
    }
}

void WindowsNetworkManager::removeNetwork(Network::Network *network)
{
    _network.remove(network);
    network->getSocket()->disconnect();
}

void WindowsNetworkManager::generateReadFs()
{
    FD_ZERO(&_readfs);
    for (std::list<Network::Network *>::iterator it = _network.begin();
         it != _network.end(); ++it)
    {
        if ((*it)->getSocket()->WindowsGetSocket() != SOCKET_ERROR)
         FD_SET((unsigned int) (*it)->getSocket()->WindowsGetSocket(), &_readfs);
    }
}

void WindowsNetworkManager::generateWriteFs()
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
                FD_SET((unsigned int)
                       (*it)->getRemoteNetwork()->getSocket()->WindowsGetSocket(), &_writefs);
            }
            else if ((*it)->getSocket()->WindowsGetSocket() != SOCKET_ERROR)
                FD_SET((unsigned int)
                       (*it)->getSocket()->WindowsGetSocket(), &_writefs);
        }
    }
}

Network::Network *WindowsNetworkManager::getUdpClient(Network::Network *remoteServer) {
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
        WindowsNetworkManager::addNetworkFromInside(client);
        _udpMapping[checkIp] = client;
        if (_slot) _slot->onClientConnected(remoteServer, client);
        LOG << "New client connected from udp://" << client->getSocket()->getRemoteIp() <<
            ":" << client->getSocket()->getRemotePort() << std::endl;
        // TODO : Delete this line
        client->getWriteBuffer()->append("hello world", 11);
        return (0);
    }
}

void WindowsNetworkManager::tcpServerReadEvent(Network::Network *net)
{
    if (!net)
        return ;
    if (!(net->getSocket()->isConnected()))
    {
        WindowsNetworkManager::removeNetwork(net);
        return ;
    }
    try {
        Network::MySocket *sock = net->getSocket()->waitForClient();
        Network::Network  *client = new Network::Network(sock);
        client->setRemoteNetwork(net);
        WindowsNetworkManager::addNetwork(client);
        LOG << "New client connected from tcp://" << client->getSocket()->getRemoteIp() <<
            ":" << client->getSocket()->getRemotePort() << std::endl;
    } catch (NetworkDisconnect &) {
        LOGERR << "Server disconnected from tcp://" << net->getSocket()->getRemoteIp() <<
            ":" << net->getSocket()->getRemotePort() << std::endl;
        if (_slot) _slot->onDisconnect(net);
        WindowsNetworkManager::removeNetwork(net);
    }
}

void WindowsNetworkManager::tcpClientReadEvent(Network::Network *net)
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
        WindowsNetworkManager::removeNetwork(net);
        throw;
    }
}

void WindowsNetworkManager::udpClientWriteEvent(Network::Network *net)
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
        WindowsNetworkManager::removeNetwork(net);
        throw;
    }
}

void WindowsNetworkManager::udpServerReadEvent(Network::Network *net)
{

    try {
        UInt16 byteRead = net->getSocket()->readFrom(&_udpReceivedIp, &_udpReceivedPort,
                                   _mainBuffer,
                                   EACH_READ_SIZE);

        WindowsNetworkManager::getUdpClient(net);
        LOG << " ReadEvent (" << byteRead << " bytes read)" << std::endl;
        if (_slot) _slot->onRead(net, net);
        net->getReadBuffer()->append(_mainBuffer, byteRead);
    } catch (NetworkDisconnect &) {
        if (_slot) _slot->onDisconnect(net);
        WindowsNetworkManager::removeNetwork(net);
        throw;
    }
}

void WindowsNetworkManager::readEvent(Network::Network *net)
{
    if (!net)
        return ;
  if (!(net->getSocket()->isConnected()))
   {
        WindowsNetworkManager::removeNetwork(net);
        return ;
   }

    if (net->getSocket()->isServerSock())
    {
        if (net->getSocket()->getType() == Network::ISocket::TCP) {
            WindowsNetworkManager::tcpServerReadEvent(net);
        } else {
            WindowsNetworkManager::udpServerReadEvent(net);
        }
    } else {
         if (net->getSocket()->getType() == Network::ISocket::TCP) {
            WindowsNetworkManager::tcpClientReadEvent(net);
         } else {
            // Cannot exist
         }
    }
}

void WindowsNetworkManager::writeEvent(Network::Network *net)
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
                    if (WindowsNetworkManager::isAClientFrom(*it, net)) {
                        if ((*it)->getWriteBuffer()->getReadSize() > 0) {
                            WindowsNetworkManager::udpClientWriteEvent(*it);
                        }
                    }
            }
        } else {
            // cannot happen
        }
    }
}

void  WindowsNetworkManager::parseNetworkList()
{
    while (1)
    {
        try {
        for (std::list<Network::Network *>::iterator it = _network.begin(); it != _network.end()
             ; ++it)
        {
            if ((*it)->getSocket() && (*it)->getSocket()->WindowsGetSocket() != SOCKET_ERROR &&
                    FD_ISSET( (unsigned int)
                        (*it)->getSocket()->WindowsGetSocket(), &_readfs))
            {
                WindowsNetworkManager::readEvent(*it);
                FD_CLR((unsigned int)
                        (*it)->getSocket()->WindowsGetSocket(), &_readfs);
                break;
            }
            else if ((*it)->getSocket() && (*it)->getSocket()->WindowsGetSocket() != SOCKET_ERROR
                     && FD_ISSET( (unsigned int)
                         (*it)->getSocket()->WindowsGetSocket(), &_writefs))
            {
                WindowsNetworkManager::writeEvent(*it);
                FD_CLR((unsigned int) (*it)->getSocket()->WindowsGetSocket(), &_readfs);
                break;
            }
        }
        return ;
        } catch (...) {}
    }
}

void WindowsNetworkManager::run(long msTimeout)
{
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = msTimeout  *1000;
    WindowsNetworkManager::generateWriteFs();

    WindowsNetworkManager::generateReadFs();
    libc::Memcpy(&_readfscpy, &_readfs, sizeof(fd_set));
    if (::select(_maxfd + 1, &_readfs, (_hasWriteFs == true) ? &_writefs : NULL, NULL,
                 (msTimeout == -1) ? NULL : &timeout) == -1)
    {
        return ;
    }
    WindowsNetworkManager::parseNetworkList();
}

void WindowsNetworkManager::setSlotListener(Network::NetworkManagerSlot *slot)
{
    _slot = slot;
}
#endif
