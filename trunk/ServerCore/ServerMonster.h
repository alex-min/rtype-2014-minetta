#ifndef SERVERMONSTER_H
#define SERVERMONSTER_H
#include "SystemDefines.h"

class ServerMonster
{
public:
    ServerMonster();
    void          erase();
    void          invalidateEvent();
    UInt16        getId() const;
    void          setId(UInt16 id);
    UInt32        getPopDelay() const;
    bool          update(UInt32 time);
    void          setPopDelay(UInt32 popDelay);

private:
    UInt16          _id;
    UInt32          _popDelay;
};

#endif // SERVERMONSTER_H
