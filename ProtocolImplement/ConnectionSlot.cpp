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
    LOGERR << "Connected Slot" << std::endl;
    ServerCore *core = reinterpret_cast<ServerCore *> (c);
    (void) isOnTimeout;
    if (!packet || !proto)
        return ;
    Protocol::StatusId _s;
    _s = Protocol::OK;
    proto->send(packet->getNetwork(), Protocol::STATUS, &_s, sizeof(Protocol::StatusId));
    String login = proto->getLoginFromData(packet->getData(), packet->getHeader()._len);
    LOGERR << "login (proto->getPointer()) => " << proto->getPointer() << std::endl;
    if (proto->getPointer() == NULL) {
    if (login == "" || login.length() >= 25)
        ConnectionSlot::sendConnected(proto, packet->getNetwork(), Protocol::FAILED, -1);
    else {
        ServerDataSingle::getInstance()->lock();
        Protocol::LoginMapper &loginMapper = ServerDataSingle::getInstance()->getMapper();
        if (core->getLoginMapper().exist(login)) {
            ConnectionSlot::sendConnected(proto, packet->getNetwork(), Protocol::USED, -1);
        } else {
            PlayerInfo *p = loginMapper.addPlayer(login);
            core->getLoginMapper().addPlayer(p);
            p->setNetwork(packet->getNetwork());
            ConnectionSlot::sendConnected(proto, packet->getNetwork(), Protocol::OK, p->getId());
        }
}
    }
        if (proto->getPointer() != NULL) {
            ServerGame *g = reinterpret_cast < ServerGame *> (proto->getPointer());
            Protocol::LoginMapper &loginMapper =
                    g->getMapper();
           if (!(loginMapper.exist(login))) {
            PlayerInfo *p = loginMapper.addPlayer(login);
            LOGERR << "Network pointer is powerful : " << packet->getNetwork() << std::endl;
            p->setNetwork(packet->getNetwork());
            if (loginMapper.getMapperList().size() == g->getMaxNbPlayer()) {
                g->sendStartGame();
            }
           }
        }
        ServerDataSingle::getInstance()->release();
}
