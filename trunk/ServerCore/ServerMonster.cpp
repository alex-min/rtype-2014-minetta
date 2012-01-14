#include "ServerMonster.h"

ServerMonster::ServerMonster()
{
    ServerMonster::erase();
}

void          ServerMonster::erase()
{
    _id = 0;
    _popDelay = 0;
}

UInt16        ServerMonster::getId() const
{
    return (_id);
}

void          ServerMonster::setId(UInt16 id)
{
    _id = id;
}

UInt32        ServerMonster::getPopDelay() const
{
    return (_popDelay);
}

bool          ServerMonster::update(UInt32 time)
{
    if (time > _popDelay)
        _popDelay = 0;
    else
        _popDelay -= time;
    return (_popDelay == 0);
}

void          ServerMonster::setPopDelay(UInt32 popDelay)
{
    _popDelay = popDelay;
}


void          ServerMonster::invalidateEvent()
{
   // @@stub
}
