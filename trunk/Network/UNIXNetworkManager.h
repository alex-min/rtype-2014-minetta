#ifndef UNIXNETWORKMANAGER_H
#define UNIXNETWORKMANAGER_H
#include "INetworkManager.h"
#include "Network.h"
#include <list>
#include <sys/select.h>
#include "MySocket.h"
#include "NetworkManagerSlot.h"

class UNIXNetworkManager
{
public:
    enum {EACH_READ_SIZE = 512};
    UNIXNetworkManager();
    virtual void addNetwork(Network::Network *network);
    virtual void addNetwork(Network::MySocket *sock);
    virtual void removeNetwork(Network::Network *network);
    virtual void run(long msTimeout);
    virtual void setSlotListener(Network::NetworkManagerSlot *slot);

private:
    void    parseNetworkList();

private:
    void generateReadFs();
    void generateWriteFs();
    void readEvent(Network::Network *net);
    void writeEvent(Network::Network *net);
    void udpServerReadEvent(Network::Network *net);
    Network::Network *getUdpClient(Network::Network *remoteServer);

protected:
    fd_set  _readfs;
    fd_set  _writefs;
    fd_set  _readfscpy;
    std::list<Network::Network *> _network;
    int     _maxfd;
    bool    _hasWriteFs;
    char    *_mainBuffer;
    Network::IpAddress _udpReceivedIp;
    UInt16             _udpReceivedPort;
    Network::NetworkManagerSlot *_slot;
    std::map<UInt64, Network::Network *> _udpMapping;
};

#endif // UNIXNETWORKMANAGER_H
