#include <iostream>
#include "IpAddress.h"
#include "MySocket.h"
#include "MyNetworkManager.h"
#include "Protocol.h"
#include "ProtocolImplement.h"
#include "ServerCore.h"

#ifndef COMMON_MODULE
#error "Common module not found"
#endif

int	main(int ac, char **av)
{
    (void) ac;
    (void) av;
    try {
        ServerCore core;
        core.start(5050);
    } catch (...) {
        std::cerr << "Program stopped with exception" << std::endl;
    }

  return (0);
}
