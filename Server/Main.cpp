#include <iostream>
#include "IpAddress.h"
#include "MySocket.h"
#include "MyNetworkManager.h"
#include "Protocol.h"
#include "ProtocolImplement.h"
#include "ServerCore.h"
#include "TimerPool.h"

#ifdef OS_WINDOWS
#include <windows.h>
#define srandom(a) srand(a)
#endif

#ifndef COMMON_MODULE
#error "Common module not found"
#endif

int	main(int ac, char **av)
{
    (void) ac;
    (void) av;
    srandom(time(NULL));

    try {
        ServerCore core;
        core.start(5050);
    } catch (...) {
        std::cerr << "Program stopped with exception" << std::endl;
    }

  return (0);
}
