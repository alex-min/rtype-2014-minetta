#include "MoveSlot.h"
#include <QString>

MoveSlot::MoveSlot()
{

}

void MoveSlot::onCall(bool isOnTimeout, Packet *packet, Protocol::Protocol *proto, void *data)
{
    if (isOnTimeout || !packet || !proto || !data)
        return;

    emit posChanged();
}

void    MoveSlot::sendNewPlayerPos(Protocol::Protocol *proto, Network::Network *net, int playerId, float x, float y)
{
    QString data;
    //temporary code
    data += QString::number(playerId) + ":" + QString::number(x) + ";" + QString::number(y);

    proto->send(net, Protocol::MOVE, data.toStdString().c_str(), data.length());
}
