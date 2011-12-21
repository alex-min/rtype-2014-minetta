#include <iostream>
#include "IpAddress.h"
#include "MySocket.h"
#include "MyNetworkManager.h"

#ifndef COMMON_MODULE
#error "Common module not found"
#endif

int	main(int ac, char **av)
{
    (void) ac;
    (void) av;
    try {
    Network::MyNetworkManager m;
    Network::MySocket sock;

    sock.createUDPServerSocket(4244);

    m.addNetwork(&sock);
    while (1) {
        m.run(100);
    }
    } catch (...) {
        std::cerr << "Program stopped with exception" << std::endl;
    }

  return (0);
}
