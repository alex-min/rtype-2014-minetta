#include <QMetaType>
#include "RefGameSlot.h"

RefGameSlot::RefGameSlot()
{

}

void    RefGameSlot::joinGame(Protocol::Protocol *proto, Network::Network *net, std::string const &gameName)
{
    unsigned int tmpLen = 0;

    libc::Memadd(_tmpBuffer, gameName.c_str(), gameName.size() + 1, tmpLen);

    proto->send(net, Protocol::JOIN_GAME, _tmpBuffer, tmpLen);
}

void    RefGameSlot::onCall(bool isOnTimeout, Packet *packet, Protocol::Protocol *proto, void *data)
{
    if (isOnTimeout || !packet || !proto || !data)
        return ;

    unsigned int tmpLen = 0;
    bool ok = false;

    Protocol::StatusId status = libc::Memextract<Protocol::StatusId>(packet->getData(), sizeof(Protocol::StatusId), tmpLen);
    UInt16 port = libc::Memextract<UInt16>(packet->getData(), sizeof(UInt16), tmpLen);


    if (status == Protocol::OK)
        ok = true;

    qRegisterMetaType<UInt16>("UInt16");

    emit gameAccess(ok, port);
}
