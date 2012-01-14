#ifndef SERVERDATA_H
#define SERVERDATA_H
#include "Mutex.h"
#include "Singleton.h"
#include "LoginMapper.h"

class ServerData
{
    friend class Singleton< ServerData >;
private:
    ServerData();
public:
    void                            lock();
    void                            release();
    Protocol::LoginMapper &         getMapper();
    Protocol::LoginMapper const &   getMapper() const;

protected:
    Mutex                       _m;
    Protocol::LoginMapper       _mapper;
};

typedef Singleton< ServerData > ServerDataSingle;

#endif // SERVERDATA_H
