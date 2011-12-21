#ifdef OS_WINDOWS
#include "WindowsSocket.h"

namespace Network {

sockaddr_in addressToSockAddr(Network::IpAddress const &ip, UInt16 port)
    {
        sockaddr_in addr;
        libc::ZeroMemory(&addr, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr=inet_addr(ip.toString().c_str());
        addr.sin_port=htons(port);
        return (addr);
    }


void sockAddrToAddress(Network::IpAddress *ip, sockaddr_in const & sin)
    {
        ip->set(sin.sin_addr.s_addr);
    }

void startNetwork()
    {
        static bool networkStarted = false;
        if (networkStarted == false) {
            WSADATA wsaData;
            libc::ZeroMemory(&wsaData, sizeof(WSADATA));
            int result = WSAStartup(MAKEWORD(2,2), &wsaData);
            if (result != 0) {
                throw NetworkDisconnect("Win32: Cannot start network on startnetwork()");
            }
        }
        networkStarted = true;
    }

/* BEGIN CLASS */

WindowsSocket::WindowsSocket()
{
    _sock = SOCKET_ERROR;
    _max_client = 200;
    _client_connected = 0;
    _isServerSock = false;
    _port = 0;
    _type = ISocket::NOT_CONNECTED;
}

WindowsSocket::WindowsSocket(int sock, struct sockaddr_in sin, unsigned short port)
{
    _sock = sock;
    _sin = sin;
    _ip.assign(::inet_ntoa(_sin.sin_addr));
    _port = port;
    _isServerSock = false;
    _type = ISocket::TCP;
}

bool            WindowsSocket::connect(Network::IpAddress const & remote, UInt16 port,
                                ISocket::SockType type)
{
    if (type == ISocket::TCP)
         return (TCPConnect(remote, port));
    return (UDPConnect(remote, port));
}

bool            WindowsSocket::TCPConnect(Network::IpAddress const & remote, UInt16 port)
{
    Network::startNetwork();
    WindowsSocket::disconnect();
    _isServerSock = false;
    _sin = Network::addressToSockAddr(remote, port);
     _sock = socket(AF_INET, SOCK_STREAM, 0);
     _type = ISocket::TCP;
     if (_sock < 0)
         return (false);
     LOG << "[+] Connecting... to " << inet_ntoa(_sin.sin_addr) << std::endl;
     if (::connect(_sock, (sockaddr *) &_sin, sizeof(_sin)) == -1)
     {
          LOG << "[-] Connection failed" << std::endl;
          return (false);
     }
     LOG << "[+] Connection successfull" << std::endl;
     return (true);
}

bool            WindowsSocket::UDPConnect(Network::IpAddress const & remote, UInt16 port)
{
    Network::startNetwork();
    WindowsSocket::disconnect();
    _isServerSock = false;
    _sin = Network::addressToSockAddr(remote, port);
    _sock = socket(AF_INET, SOCK_DGRAM, 0);
    _udpLenTmp = sizeof(struct sockaddr_in);
    _port = port;
    _udpClientToServerIp = remote;
    _udpClientToServerPort = port;
    _type = ISocket::UDP;
    if (_sock != SOCKET_ERROR)
        return (true);
    return (false);
}


void            WindowsSocket::disconnect()
{
    if (_sock != SOCKET_ERROR)
        ::closesocket(_sock);
    _sock = SOCKET_ERROR;
    _type = ISocket::NOT_CONNECTED;
}


UInt16           WindowsSocket::sendTo(Network::IpAddress const &remote, UInt32 port,
                                    const void *data, UInt32 len)
{
    Network::startNetwork();

    if (!WindowsSocket::isConnected() || _type != ISocket::UDP)
        throw NetworkDisconnect();

    sockaddr_in sin = Network::addressToSockAddr(remote, port);

   Int16 ret = ::sendto(_sock, reinterpret_cast<const char *> (data), len,
                        0, (struct sockaddr *) &sin, sizeof(sin));

    if (ret == 0 || ret == -1)
    {
        WindowsSocket::disconnect();
        throw NetworkDisconnect();
    }
    return (ret);
}

UInt16           WindowsSocket::send(const void *data, UInt32 len)
{
    Network::startNetwork();

    LOG << "here" << std::endl;
    if (!WindowsSocket::isConnected())
        throw NetworkDisconnect("not connected");
    LOG << "here" << std::endl;
    if (_type == ISocket::TCP)
    {
        LOG << "here" << std::endl;

        UInt16 ret = ::send(_sock, reinterpret_cast<const char *> (data), len, 0);
        if (ret == 0 || ret == -1)
        {
            WindowsSocket::disconnect();
            throw NetworkDisconnect("Disconnected");
        }
        return (ret);
    }
    else
       return (WindowsSocket::sendTo(_udpClientToServerIp, _udpClientToServerPort, data, len));
}


UInt16           WindowsSocket::readFrom(Network::IpAddress *remote, UInt32 *port, void *data, UInt32 len)
{
    Network::startNetwork();

    if (!WindowsSocket::isConnected() || !remote || !port)
        throw NetworkDisconnect();
    UInt16 size = ::recvfrom(_sock, reinterpret_cast<char *>(data),
                             len, 0, (struct sockaddr *) &_udpSinTmp, &_udpLenTmp);
    remote->set(_udpSinTmp.sin_addr.s_addr);
    *port = _udpSinTmp.sin_port;
    if (size == 0 || size == -1)
    {
        WindowsSocket::disconnect();
        throw NetworkDisconnect();
    }
    return (size);
}


Int16           WindowsSocket::read(void *data, UInt32 len)
{
    Network::startNetwork();

    if (!WindowsSocket::isConnected())
        throw NetworkDisconnect();
    Int16 size = ::recv(_sock, reinterpret_cast<char *>(data), len, 0);
    return (size);
}

bool            WindowsSocket::isServerSock() const
{
    return (_isServerSock);
}

UInt16          WindowsSocket::getPort() const
{
    return (_port);
}

WindowsSocket *    WindowsSocket::waitForClient()
{
    Network::startNetwork();

    int                   csock;
    int                   client_sin_len;
    struct sockaddr_in    client_sin;

    client_sin_len = sizeof(struct sockaddr_in);
    csock = accept(_sock, (struct sockaddr *) &client_sin,
                   (socklen_t *) &client_sin_len);
    if (csock == SOCKET_ERROR)
        throw NetworkDisconnect();
    return (new WindowsSocket(csock, client_sin, _port));
}


bool           WindowsSocket::createServerSocket(UInt16 port, ISocket::SockType type)
{
    if (type == ISocket::TCP)
        return (createTCPServerSocket(port));
    return (createUDPServerSocket(port));
}


bool            WindowsSocket::createTCPServerSocket(UInt16 port)
{
    char         enable;

    Network::startNetwork();
    _isServerSock = true;
    enable = 1;
    _sock = socket(AF_INET, SOCK_STREAM, 0);
    ::setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
    if (_sock == SOCKET_ERROR)
      {
        std::cout << "[-] Cannot create server socket" << std::endl;
        return (false);
      }
    _sin.sin_family = AF_INET;
    _sin.sin_port = htons(port);
    _sin.sin_addr.s_addr = INADDR_ANY;
    if (bind(_sock, (struct sockaddr*) &_sin, sizeof(struct sockaddr_in)) == -1
        || listen(_sock, 42) == -1)
      {
         std::cout << "[-] Cannot create server socket" << std::endl;
        return (false);
      }
    _ip.assign(::inet_ntoa(_sin.sin_addr));
    _port = port;
   return (true);
}


bool            WindowsSocket::createUDPServerSocket(UInt16 port)
{
    Network::startNetwork();

    struct sockaddr_in servaddr;
      _sock=socket(AF_INET,SOCK_DGRAM,0);
      if (_sock == SOCKET_ERROR) {
          std::cout << "[-] Cannot create server socket" << std::endl;
          return (false);
      }

      libc::ZeroMemory(&servaddr, sizeof(servaddr));
      servaddr.sin_family = AF_INET;
      servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
      servaddr.sin_port=htons(port);
      if (::bind(_sock,(struct sockaddr *)&servaddr,sizeof(servaddr)) == -1) {
          std::cout << "[-] Cannot create server socket" << std::endl;
          return (false);
      }
      return (true);
}


bool            WindowsSocket::isConnected()
{
    if (_sock != SOCKET_ERROR)
        return (true);
    return (false);
}

Int32           WindowsSocket::WindowsGetSocket() const {
    return (_sock);
}



} // !namespace : Network

#endif