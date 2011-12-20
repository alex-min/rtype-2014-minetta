#ifndef MYSOCKET_H
#define MYSOCKET_H
#ifdef OS_WINDOWS
#include "WindowsSocket.h"
namespace Network {
typedef WindowsSocket MySocket;
} // !namespace : Network
#elif defined OS_UNIX
#include "UNIXSocket.h"
namespace Network {
typedef class UNIXSocket MySocket;
}
#else
#error "MySocket.h : Framwork doesnt have a socket implementation for your operating system"
#endif

#endif // MYSOCKET_H
