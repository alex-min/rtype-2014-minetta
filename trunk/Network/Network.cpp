#include "Network.h"

namespace Network {
Network::Network(unsigned int readCirbufSize, unsigned int writeCirbufSize) :
         _socket(new MySocket),
        _readBuf(readCirbufSize),
        _writeBuf(writeCirbufSize),
        _net(NULL)
{
}

Network::Network(MySocket *sock, unsigned int readCirbufSize, unsigned int writeCirbufSize) :
         _socket(sock),
        _readBuf(readCirbufSize),
        _writeBuf(writeCirbufSize)
{
}

std::string const &Network::getName() const
{
    return (_name);
}

void Network::setName(std::string const &name)
{
    _name = name;
}

MySocket *Network::getSocket()
{
    return (_socket);
}

MySocket *Network::getSocket() const
{
    return (_socket);
}

void Network::setSocket(MySocket *sock)
{
    _socket = sock;
}


CircularBuffer *Network::getReadBuffer()
{
    return (&_readBuf);
}

CircularBuffer *Network::getWriteBuffer()
{
    return (&_writeBuf);
}

Network    *   Network::getRemoteNetwork() const
{
    return (_net);
}

void                Network::setRemoteNetwork(Network *net)
{
    _net = net;
}


} // !namespace : Network
