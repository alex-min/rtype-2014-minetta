#ifndef NETWORK_H
#define NETWORK_H
#include <map>
#include "ISocket.h"
#include "CircularBuffer.h"
#include "MySocket.h"

namespace Network {
class Network
{

public:
    Network(unsigned int readCirbufSize = 4096, unsigned int writeCirbufSize = 4096);
    Network(MySocket *sock, unsigned int readCirbufSize = 4096, unsigned int writeCirbufSize = 4096);
    CircularBuffer *    getReadBuffer();
    CircularBuffer *    getWriteBuffer();
    MySocket *          getSocket();
    void                setSocket(MySocket *sock);
    std::string const & getName() const;
    void                setName(std::string const &);

protected:
    std::string         _name;
    MySocket *    _socket;
    CircularBuffer      _readBuf;
    CircularBuffer      _writeBuf;
};
}
#endif // NETWORK_H
