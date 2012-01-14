#include "ServerData.h"

ServerData::ServerData()
{
    _m.create();
}


void                            ServerData::lock()
{
    _m.lock();
}

void                            ServerData::release()
{
    _m.unlock();
}

Protocol::LoginMapper &         ServerData::getMapper()
{
    return (_mapper);
}

Protocol::LoginMapper const &   ServerData::getMapper() const
{
    return (_mapper);
}
