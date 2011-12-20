#ifndef WINDOWSSOCKET_H
#define WINDOWSSOCKET_H
#include "ISocket.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <windows.h>
#include "LibC.h"
#include "NetworkDisconnect.h"

namespace Network {
    sockaddr_in addressToSockAddr(Network::IpAddress const &ip, UInt16 port);
    void sockAddrToAddress(Network::IpAddress *ip, sockaddr_in const & sin);
    void startNetwork();

class WindowsSocket : public APortableSocket
{
public:
    WindowsSocket();
    virtual bool            connect(Network::IpAddress const & remote, UInt16 port,
                                    ISocket::SockType type = ISocket::TCP);
    virtual bool            TCPConnect(Network::IpAddress const & remote, UInt16 port);
    virtual bool            UDPConnect(Network::IpAddress const & remote, UInt16 port);

    virtual void            disconnect();

    virtual UInt16           sendTo(Network::IpAddress const &remote, UInt32 port,
                                    const void *data, UInt32 len);
    virtual UInt16           send(const void *data, UInt32 len);

    // return : size of byte written in buf;
    virtual UInt16           readFrom(Network::IpAddress *remote, UInt32 *port, void *data, UInt32 len);
    virtual UInt16           read(void *data, UInt32 len);
    // return : size of byte written in buf
    virtual bool            isServerSock() const;
    virtual UInt16          getPort() const;
    virtual WindowsSocket *    waitForClient();

    virtual bool            createServerSocket(UInt16 port, ISocket::SockType type = ISocket::TCP);
    virtual bool            createTCPServerSocket(UInt16 port);
    virtual bool            createUDPServerSocket(UInt16 port);
    virtual bool            isConnected();


 public:
    Int32 WindowsGetSocket() const;

private:
    WindowsSocket(int sock, struct sockaddr_in sin, unsigned short port);

private:
    bool createClientSock();

protected:
    Network::IpAddress      _udpClientToServerIp;
    Int16                   _udpClientToServerPort;
    int                     _sock;
    struct sockaddr_in      _sin;
    struct sockaddr_in      _udpSinTmp;
    socklen_t               _udpLenTmp;
    bool                    _isServerSock;
    std::string             _ip;
    char                    _ipbuf[30];
};

} // !namespace : Network

#endif // WINDOWSSOCKET_H
