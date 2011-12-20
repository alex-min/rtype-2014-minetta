#ifndef MYNETWORKMANAGER_H
#define MYNETWORKMANAGER_H
#ifdef OS_WINDOWS
#include "WindowsSocket.h"
namespace Network {
typedef WindowsSocket MySocket;
} // !namespace : Network
#elif defined OS_UNIX
#include "UNIXNetworkManager.h"
namespace Network {
typedef class UNIXNetworkManager MyNetworkManager;
}
#else
#error "MyNetworkManager.h : Framwork doesnt have a socket implementation for your operating system"
#endif
#endif // MYNETWORKMANAGER_H
