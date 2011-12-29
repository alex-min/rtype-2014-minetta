#include "ConnectionSlot.h"
#include "ServerCore.h"

ConnectionSlot::ConnectionSlot()
{
}

void    ConnectionSlot::sendConnected(Protocol::Protocol *p, Network::Network *n,
                                             Protocol::StatusId stat, UInt16 id)
{
    if (!p)
        return ;
    libc::Memcpy(_tmpBuffer, &stat, sizeof(Protocol::StatusId));
    libc::Memcpy(_tmpBuffer + sizeof(Protocol::StatusId), &id, sizeof(UInt16));
    p->send(n, Protocol::CONNECTED, _tmpBuffer, sizeof(Protocol::StatusId) + sizeof(UInt16));
}


void ConnectionSlot::onCall(bool isOnTimeout, Packet *packet, Protocol::Protocol *proto, void *c)
{
    ServerCore *core = reinterpret_cast<ServerCore *> (c);
    (void) isOnTimeout;
    if (!packet || !proto)
        return ;
    Protocol::StatusId _s;
    _s = Protocol::OK;
    proto->send(packet->getNetwork(), Protocol::STATUS, &_s, sizeof(Protocol::StatusId));
    LOGERR << "here" << std::endl;
    String login = proto->getLoginFromData(packet->getData(), packet->getHeader()._len);
    if (login == "" || login.length() >= 25)
        sendConnected(proto, packet->getNetwork(), Protocol::FAILED, -1);
    else {
        ServerDataSingle::getInstance()->lock();
        Protocol::LoginMapper &loginMapper = ServerDataSingle::getInstance()->getMapper();
        if (loginMapper.exist(login)) {
            ConnectionSlot::sendConnected(proto, packet->getNetwork(), Protocol::USED, -1);
        } else {
        }

        ServerDataSingle::getInstance()->release();
    }
}
