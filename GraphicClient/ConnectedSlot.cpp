#include "ConnectedSlot.h"

ConnectedSlot::ConnectedSlot()
{
}

void ConnectedSlot::sendConnect(std::string const &login, Protocol::Protocol *proto, Network::Network *net)
{
    unsigned int tmpLen = 0;

    libc::Memadd(_tmpBuffer, login.c_str(), login.size() + 1, tmpLen);


    proto->send(net, Protocol::CONNECT, _tmpBuffer, tmpLen);
}

void ConnectedSlot::onCall(bool isOnTimeout, Packet *packet, Protocol::Protocol *proto, void *data)
{
    if (isOnTimeout || !packet || !proto || !data)
        return ;

    unsigned int tmpLen = 0;

    Protocol::StatusId status = libc::Memextract<Protocol::StatusId>(packet->getData(), sizeof(Protocol::StatusId), tmpLen);
    short id  = libc::Memextract<short>(packet->getData(), sizeof(short), tmpLen);
    bool ok = false;

    if (status == Protocol::OK)
        ok = true;

    LOG << status << std::endl;
    emit connected(ok, id);
}
