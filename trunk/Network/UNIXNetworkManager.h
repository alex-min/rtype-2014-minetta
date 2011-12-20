#ifndef UNIXNETWORKMANAGER_H
#define UNIXNETWORKMANAGER_H
#include "INetworkManager.h"
#include "Network.h"
#include <list>
#include <sys/select.h>


class UNIXNetworkManager
{
public:
    UNIXNetworkManager();
    virtual void addNetwork(Network::Network *network);
    virtual void removeNetwork(Network::Network *network);
    virtual void run(long uTimeout);


private:
    void generateReadFs();
    void generateWriteFs();

protected:
    fd_set  _readfs;
    fd_set  _writefs;
    fd_set  _readfscpy;
    std::list<Network::Network *> _network;
    int     _maxfd;
    bool    _hasWriteFs;
    char    *_mainBuffer;
};

#endif // UNIXNETWORKMANAGER_H
