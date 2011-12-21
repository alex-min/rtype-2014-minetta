#ifndef ISOCKET_H
#define ISOCKET_H
#include "IpAddress.h"

namespace Network {
class ISocket
{
public:
    enum SockType {TCP, UDP, NOT_CONNECTED};
    virtual bool            connect(Network::IpAddress const & remote, UInt16 port,
                                    ISocket::SockType type = ISocket::TCP) = 0;
    virtual bool            TCPConnect(Network::IpAddress const & remote, UInt16 port)  = 0;
    virtual bool            UDPConnect(Network::IpAddress const & remote, UInt16 port) = 0;
    virtual void            UDPConnectWithoutSocket(Network::IpAddress const &remote, UInt16 port) = 0;

    virtual void            disconnect() = 0;

    virtual UInt16           sendTo(Network::IpAddress const &remote, UInt32 port,
                                    const void *data, UInt32 len) = 0;
    virtual UInt16           send(const void *data, UInt32 len) = 0;

    // return : size of byte written in buf;
    virtual UInt16           readFrom(Network::IpAddress *remote,
                                      UInt16 *port, void *data, UInt32 len) = 0;
    virtual UInt16           read(void *data, UInt32 len) = 0;
    // return : size of byte written in buf
    virtual bool            isServerSock() const = 0;
    virtual UInt16          getPort() const = 0;
    virtual ISocket *    waitForClient() = 0;

    virtual bool            createServerSocket(UInt16 port, ISocket::SockType type = ISocket::TCP) = 0;
    virtual bool            createTCPServerSocket(UInt16 port) = 0;
    virtual bool            createUDPServerSocket(UInt16 port) = 0;
    virtual bool            isConnected() = 0;
    virtual SockType        getType() const = 0;

};

class APortableSocket : public ISocket
{
public:
    bool createServerSockFromRange(unsigned int begin, unsigned int end);

protected:
    SockType    _type;
    static int _total_client_connected;
    int _client_connected;
    int _max_client;
    unsigned short _port;
};

} // !namespace : Network

#endif // ISOCKET_H
