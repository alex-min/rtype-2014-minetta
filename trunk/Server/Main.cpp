#include <iostream>
#include "IpAddress.h"
#include "MySocket.h"

#ifndef COMMON_MODULE
#error "Common module not found"
#endif

int	main(int ac, char **av)
{
    try {
    Network::MySocket *lol = new Network::MySocket;
    Network::IpAddress i(127,0,0,1);

    if (lol->UDPConnect("10.18.207.136", 32000) == false) {
        LOGERR << "Cannot connect" << std::endl;
        return (0);
    }
    lol->send("lol", 3);
    Network::IpAddress ip;
    UInt32 port;
    char data[20];
    UInt8 res = lol->readFrom(&ip, &port, data, 20);
    std::cout << data << " " << (int)res << std::endl;
    } catch (...) {
        std::cerr << "Program stopped with exception" << std::endl;
    }

  return (0);
}
