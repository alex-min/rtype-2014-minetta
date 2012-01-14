#include "UNIXSocket.h"
#include <errno.h>
#include <stdio.h>
#ifdef OS_UNIX

namespace Network {

sockaddr_in addressToSockAddr(Network::IpAddress const &ip, UInt16 port)
    {
        sockaddr_in addr;
        libc::ZeroMemory(&addr, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr= ip.toInt();
        addr.sin_port=htons(port);
        return (addr);
    }


void sockAddrToAddress(Network::IpAddress *ip, sockaddr_in const & sin)
    {
        ip->set(sin.sin_addr.s_addr);
    }

/* BEGIN CLASS */

UNIXSocket::UNIXSocket()
{
    _sock = SOCKET_ERROR;
    _fakesocketreference = SOCKET_ERROR;
    _max_client = 200;
    _client_connected = 0;
    _isServerSock = false;
    _port = 0;
    _fakesocket = false;
    _type = ISocket::NOT_CONNECTED;
    _udpLenTmp = sizeof(struct sockaddr_in);

}

UNIXSocket::UNIXSocket(int sock, struct sockaddr_in sin, unsigned short port)
{
    _fakesocket = false;
    _sock = sock;
    _sin = sin;
    _ip.assign(::inet_ntoa(_sin.sin_addr));
    _port = port;
    _isServerSock = false;
    _type = ISocket::TCP;
    _udpLenTmp = sizeof(struct sockaddr_in);
    UNIXSocket::setRemoteIp(sin.sin_addr.s_addr);
    UNIXSocket::setRemotePort(ntohs(sin.sin_port));
}

bool            UNIXSocket::connect(Network::IpAddress const & remote, UInt16 port,
                                ISocket::SockType type)
{
    if (type == ISocket::TCP)
         return (TCPConnect(remote, port));
    return (UDPConnect(remote, port));
}

bool            UNIXSocket::TCPConnect(Network::IpAddress const & remote, UInt16 port)
{
    UNIXSocket::disconnect();
    _isServerSock = false;
    _sin = Network::addressToSockAddr(remote, port);
     _sock = socket(AF_INET, SOCK_STREAM, 0);
     _type = ISocket::TCP;
     if (_sock < 0)
         return (false);
     if (::connect(_sock, (sockaddr *) &_sin, sizeof(_sin)) == -1)
     {
          LOG << "[-] Connection failed" << std::endl;
          return (false);
     }
     LOG << "[+] Connection successfull" << std::endl;
     return (true);
}

bool            UNIXSocket::UDPConnect(Network::IpAddress const & remote, UInt16 port)
{
    UNIXSocket::disconnect();
    _isServerSock = false;
    _sin = Network::addressToSockAddr(remote, port);
    _sock = socket(AF_INET, SOCK_DGRAM, 0);
    _port = port;
    _udpClientToServerIp = remote;
    _udpClientToServerPort = port;
    UNIXSocket::setRemoteIp(remote);
    UNIXSocket::setRemotePort(port);
    _type = ISocket::UDP;
    if (_sock != SOCKET_ERROR)
        return (true);
    return (false);
}

void            UNIXSocket::UDPConnectWithoutSocket(Network::IpAddress const &remote,
                                                    UInt16 port,
                                                    ISocket *refsock)
{
    _fakesocketreference = dynamic_cast<UNIXSocket *> (refsock)->UNIXGetSocket();
    UNIXSocket::disconnect();
    _isServerSock = false;
    _sin = Network::addressToSockAddr(remote, port);
    _udpLenTmp = sizeof(struct sockaddr_in);
    _port = port;
    _udpClientToServerIp.set(remote.toInt());
    _udpClientToServerPort = port;
    _type = ISocket::UDP;
    _fakesocket = true;
    UNIXSocket::setRemoteIp(remote);
    UNIXSocket::setRemotePort(ntohs(_sin.sin_port));
}


void            UNIXSocket::disconnect()
{
    if (_sock != SOCKET_ERROR)
        ::close(_sock);
    _sock = SOCKET_ERROR;
    _type = ISocket::NOT_CONNECTED;
    _fakesocket = false;
}


UInt16           UNIXSocket::sendTo(Network::IpAddress const &remote, UInt32 port,
                                    const void *data, UInt32 len)
{
    if (!UNIXSocket::isConnected() || _type != ISocket::UDP)
        throw NetworkDisconnect();
    sockaddr_in sin = Network::addressToSockAddr(remote, port);
    Int16 ret = ::sendto(_sock, data, len,
                        MSG_NOSIGNAL, (struct sockaddr *) &sin, sizeof(sin));

    if (ret == 0 || ret == -1)
    {
        UNIXSocket::disconnect();
        throw NetworkDisconnect();
    }
    return (ret);
}

UInt16           UNIXSocket::sendFake(Network::IpAddress const &remote, UInt32 port,
                                const void *data, UInt32 len)
{
    if (!UNIXSocket::isConnected() || _type != ISocket::UDP)
        throw NetworkDisconnect();
    sockaddr_in sin = Network::addressToSockAddr(remote, port);

   Int16 ret = ::sendto(_fakesocketreference, data, len,
                        MSG_NOSIGNAL, (struct sockaddr *) &sin, sizeof(sin));

    if (ret == 0 || ret == -1)
    {
        UNIXSocket::disconnect();
        throw NetworkDisconnect();
    }
    return (ret);
}

UInt16           UNIXSocket::send(const void *data, UInt32 len)
{
    if (!UNIXSocket::isConnected())
        throw NetworkDisconnect();
    if (_type == ISocket::TCP)
    {
        Int16 ret = ::send(_sock, data, len, 0);
        if (ret == 0 || ret == -1)
        {
            UNIXSocket::disconnect();
            throw NetworkDisconnect();
        }
        return (ret);
    }
    else if (_fakesocket == false)
       return (UNIXSocket::sendTo(getRemoteIp(), getRemotePort(), data, len));
    else
       return (UNIXSocket::sendFake(getRemoteIp(), getRemotePort(), data, len));
}


UInt16           UNIXSocket::readFrom(Network::IpAddress *remote, UInt16 *port, void *data, UInt32 len)
{
    if (!UNIXSocket::isConnected() || !port || !data)
        throw NetworkDisconnect();
    Int16 size = ::recvfrom(_sock, data, len, 0, (struct sockaddr *) &_udpSinTmp, &_udpLenTmp);
   // LOGERR << "RECEVED from" << inet_ntoa(_udpSinTmp.sin_addr) << std::endl;
    remote->set(_udpSinTmp.sin_addr.s_addr);
    *port = ntohs(_udpSinTmp.sin_port);
    if (size == 0 || size == -1)
    {
        UNIXSocket::disconnect();
        throw NetworkDisconnect();
    }
    return (size);
}


UInt16           UNIXSocket::read(void *data, UInt32 len)
{
    if (!UNIXSocket::isConnected())
        throw NetworkDisconnect();
    Int16 size = ::recv(_sock, data, len, 0);
    if (size == 0 || size == -1)
    {
        UNIXSocket::disconnect();
        throw NetworkDisconnect();
    }
    return (size);
}

bool            UNIXSocket::isServerSock() const
{
    return (_isServerSock);
}

UInt16          UNIXSocket::getPort() const
{
    return (_port);
}

UNIXSocket *    UNIXSocket::waitForClient()
{
    int                   csock;
    int                   client_sin_len;
    struct sockaddr_in    client_sin;

    client_sin_len = sizeof(struct sockaddr_in);
    csock = accept(_sock, (struct sockaddr *) &client_sin,
                   (socklen_t *) &client_sin_len);
    if (csock == SOCKET_ERROR)
        throw NetworkDisconnect();
    UNIXSocket *sock = new UNIXSocket(csock, client_sin, _port);

    return (sock);
}


bool           UNIXSocket::createServerSocket(UInt16 port, ISocket::SockType type)
{
    if (type == ISocket::TCP)
        return (createTCPServerSocket(port));
    return (createUDPServerSocket(port));
}


bool            UNIXSocket::createTCPServerSocket(UInt16 port)
{
    int         enable;

    _isServerSock = true;
    enable = 1;
    _sock = socket(AF_INET, SOCK_STREAM, 0);
    ::setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
    if (_sock == SOCKET_ERROR)
      {
        LOGERR << "[-] Cannot create server socket" << std::endl;
        return (false);
      }
    _sin.sin_family = AF_INET;
    _sin.sin_port = htons(port);
    _sin.sin_addr.s_addr = INADDR_ANY;
    if (bind(_sock, (struct sockaddr*) &_sin, sizeof(struct sockaddr_in)) == -1
        || listen(_sock, 42) == -1)
      {
         LOGERR << "[-] Cannot create server socket" << std::endl;
        return (false);
      }
    _ip.assign(::inet_ntoa(_sin.sin_addr));
    _port = port;
    _type = ISocket::TCP;
   return (true);
}


bool            UNIXSocket::createUDPServerSocket(UInt16 port)
{
    int enable = 1;
    struct sockaddr_in servaddr;
       _isServerSock = true;
      _sock=socket(AF_INET,SOCK_DGRAM,0);
      ::setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
      //::setsockopt(_sock, SOL_SOCKET, SO_BROADCAST, &enable, sizeof(int));
      if (_sock == SOCKET_ERROR) {
          std::cout << "[-] Cannot create server socket" << std::endl;
          return (false);
      }

      libc::ZeroMemory(&servaddr, sizeof(servaddr));
      servaddr.sin_family = AF_INET;
      servaddr.sin_addr.s_addr=(INADDR_ANY);
      servaddr.sin_port=htons(port);
      if (::bind(_sock,(struct sockaddr *)&servaddr,sizeof(servaddr)) == -1) {
          std::cout << "[-] Cannot create server socket" << std::endl;
          return (false);
      }
      _type = ISocket::UDP;
      _networkport = port;
      return (true);
}


bool            UNIXSocket::isConnected()
{
    if (_type != ISocket::NOT_CONNECTED && (_sock != SOCKET_ERROR || _fakesocket == true))
        return (true);
    return (false);
}

Int32           UNIXSocket::UNIXGetSocket() const {
       return (_sock);
}

ISocket::SockType        UNIXSocket::getType() const
{
       return (_type);
}

Network::IpAddress const &UNIXSocket::getRemoteIp() const
{
    return (_networkip);
}

UInt32          UNIXSocket::getRemotePort() const
{
    return (_networkport);
}

void            UNIXSocket::setRemoteIp(Network::IpAddress const &ip)
{
    _networkip.set(ip.toInt());
}

void            UNIXSocket::setRemotePort(UInt16 port)
{
    _networkport = port;
}

} // !namespace : Network


#endif
