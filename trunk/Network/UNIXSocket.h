#ifndef UNIXSOCKET_H
#ifdef OS_UNIX
#define UNIXSOCKET_H
#include "Exception.h"
#include "ISocket.h"
#include "NetworkDisconnect.h"
#include "IpAddress.h"
#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/resource.h>


#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#else
#error "SOCKET_ERROR Should not be defined on UNIX Platform"
#endif

namespace Network {
    sockaddr_in addressToSockAddr(Network::IpAddress const &ip, UInt16 port);
    void sockAddrToAddress(Network::IpAddress *ip, sockaddr_in const & sin);

class UNIXSocket : public APortableSocket
{
public:
    UNIXSocket();
    virtual bool            connect(Network::IpAddress const & remote, UInt16 port,
                                    ISocket::SockType type = ISocket::TCP);
    virtual bool            TCPConnect(Network::IpAddress const & remote, UInt16 port);
    virtual bool            UDPConnect(Network::IpAddress const & remote, UInt16 port);
    virtual void            UDPConnectWithoutSocket(Network::IpAddress const &remote, UInt16 port);


    virtual void            disconnect();

    virtual UInt16           sendTo(Network::IpAddress const &remote, UInt32 port,
                                    const void *data, UInt32 len);
    virtual UInt16           send(const void *data, UInt32 len);

    // return : size of byte written in buf;
    virtual UInt16           readFrom(Network::IpAddress *remote, UInt16 *port, void *data, UInt32 len);
    virtual UInt16           read(void *data, UInt32 len);
    // return : size of byte written in buf
    virtual bool            isServerSock() const;
    virtual UInt16          getPort() const;
    virtual UNIXSocket *    waitForClient();

    virtual bool            createServerSocket(UInt16 port, ISocket::SockType type = ISocket::TCP);
    virtual bool            createTCPServerSocket(UInt16 port);
    virtual bool            createUDPServerSocket(UInt16 port);
    virtual bool            isConnected();
    virtual SockType        getType() const;


 public:
    Int32 UNIXGetSocket() const;

private:
    UNIXSocket(int sock, struct sockaddr_in sin, unsigned short port);

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
    bool                    _fakesocket;
};

} // !namespace : Network

#endif
#endif // UNIXSOCKET_H
