#include "ListGameSlot.h"
#include <QString>
#include <QMetaType>
#include "MyString.h"

ListGameSlot::ListGameSlot()
{

}

void ListGameSlot::requestGameList(Protocol::Protocol *proto, Network::Network *net)
{
    proto->send(net, Protocol::LIST_GAME, _tmpBuffer, 1);
}

void ListGameSlot::onCall(bool isOnTimeout, Packet *packet, Protocol::Protocol *proto, void *data)
{
    if (isOnTimeout || !packet || !proto || !data)
        return;

    unsigned int tmpLen = 0;

    UInt8 nbPlayer = libc::Memextract<UInt8>(packet->getData(), sizeof(UInt8), tmpLen);
    UInt8 nbMaxPlayer = libc::Memextract<UInt8>(packet->getData(), sizeof(UInt8), tmpLen);
    String gameName = proto->getLoginFromData(packet->getData() + 2, packet->getHeader()._len - 1);

    QString name = gameName.c_str();

    qRegisterMetaType<UInt8>("UInt8");

    emit newGame(nbPlayer, nbMaxPlayer, name);
}
