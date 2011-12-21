#ifndef NETWORKMANAGERSLOT_H
#define NETWORKMANAGERSLOT_H
#include "Network.h"

namespace Network {
class NetworkManagerSlot {
public :
    virtual void onClientConnected(Network *remote, Network *client) = 0;
    virtual void onRead(Network *remote, Network *client) = 0;
    virtual void onWrite(Network *net) = 0;
    virtual void onDisconnect(Network *net) = 0;
};
} // !namespace : Network

#endif // NETWORKMANAGERSLOT_H
