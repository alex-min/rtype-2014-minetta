#include "UNIXNetworkManager.h"

UNIXNetworkManager::UNIXNetworkManager() :
    _maxfd(-1),
    _mainBuffer(new char[4096])
{
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

void UNIXNetworkManager::run(long uTimeout)
{
    (void) uTimeout;
}
