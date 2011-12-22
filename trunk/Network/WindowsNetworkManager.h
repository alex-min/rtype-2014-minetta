#ifndef WINDOWSNETWORKMANAGER_H
#define WINDOWSNETWORKMANAGER_H
#ifdef OS_WINDOWS
#include "INetworkManager.h"
#include "Network.h"
#include <list>
#include <Winsock2.h>
#include "MySocket.h"
#include "NetworkManagerSlot.h"

class WindowsNetworkManager
{
public:
    enum {EACH_READ_SIZE = 512};
    WindowsNetworkManager();
    virtual void addNetwork(Network::Network *network);
    virtual void addNetwork(Network::MySocket *sock);
    virtual void removeNetwork(Network::Network *network);
    virtual void run(long msTimeout);
    virtual void setSlotListener(Network::NetworkManagerSlot *slot);
    virtual bool isAClientFrom(Network::Network *client, Network::Network *remote);

private:
    void    parseNetworkList();

private:
    void generateReadFs();
    void generateWriteFs();
    void readEvent(Network::Network *net);
    void writeEvent(Network::Network *net);
    void udpServerReadEvent(Network::Network *net);
    void tcpServerReadEvent(Network::Network *net);
    void tcpClientReadEvent(Network::Network *net);
    void udpClientWriteEvent(Network::Network *net);
    Network::Network *getUdpClient(Network::Network *remoteServer);
    void addNetworkFromInside(Network::Network *network);
    void addNetworkFromInside(Network::MySocket *network);


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


#endif
#endif // WINDOWSNETWORKMANAGER_H
