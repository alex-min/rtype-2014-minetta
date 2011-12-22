#include <iostream>
#include "IpAddress.h"
#include "MySocket.h"
#include "MyNetworkManager.h"
#include "Protocol.h"
#include "ProtocolImplement.h"

#ifndef COMMON_MODULE
#error "Common module not found"
#endif

int	main(int ac, char **av)
{
    (void) ac;
    (void) av;
    try {
        ConnectionSlot slot;

    Network::IpAddress p;



    Protocol::Protocol proto;

    Network::MyNetworkManager m;
    Network::MySocket sock;
    Network::MySocket tcpsock;

    proto.registerSlotType(Protocol::CONNECT, &slot);
    m.setSlotListener(&proto);

    sock.createUDPServerSocket(1216);
    tcpsock.createTCPServerSocket(5051);

    m.addNetwork(&sock);
    m.addNetwork(&tcpsock);
    while (1) {
        m.run(100);
    }
    } catch (...) {
        std::cerr << "Program stopped with exception" << std::endl;
    }

  return (0);
}
