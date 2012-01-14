#ifndef TIMERPOOL_H
#define TIMERPOOL_H
#include <map>
#include <time.h>
#include "ITime.h"
#include "Singleton.h"
#include "time.h"

template <class Packet, class ClassPtr, class FuncPtr, class Protocol>
class TimerPool {
    enum {DEFAULT_TIMEOUT = 50};
public :
TimerPool()
{
    _proto = NULL;
}

void setProtocol(Protocol *proto)
{
    _proto = proto;
}

void addToPool(Packet *pack,
               unsigned int timeout)
{
    if (!pack)
        return ;
    MyTime time;

    time.setToMsTimeOfDay();
    std::cout << "addTotimeout| " << timeout << std::endl;
    _pool[pack].first = time.getMs() + timeout;
    _pool[pack].second = std::pair<ClassPtr, FuncPtr> (pack->getSlot(), pack->getSlotCall());
}

void removeFromPool(Packet *pack)
{
    typename PoolMap::iterator it;

    if (!pack)
        return ;
    it = _pool.find(pack);
    if (it == _pool.end())
        return ;
    _pool.erase(it);
}

void autocall(Protocol *p)
{
    _time.setToMsTimeOfDay();

    typename PoolMap::iterator it = _pool.begin();
    typename PoolMap::iterator it2;
    while (it != _pool.end())
    {
       // std::cout << _time.getMs() << " => " << it->second.first << std::endl;
        if (_time.getMs() > it->second.first)
        {
            if (it->second.second.first && it->second.second.second)
              (it->second.second.first->*it->second.second.second)(true, it->first, p);
            it2 = it;
            if (it->first && _proto)
              _proto->unregisterPacket(it->first);
            ++it;


            _pool.erase(it2);
        }
        else
        ++it;
    }

}

int getMsNextCall(Protocol *p)
{
    long long time = -1;

    _time.setToMsTimeOfDay();

    for (typename PoolMap::iterator it = _pool.begin(); it != _pool.end(); ++it)
    {
        if (it->second.first < static_cast<unsigned int>(time) || time < 0)
            time =it->second.first;
    }
    if (time == -1)
        return (DEFAULT_TIMEOUT);
    if (_time.getMs() > static_cast<unsigned long long>(time))
    {
        autocall(p);
        return (getMsNextCall(p));
    }
    if (static_cast<unsigned int>(time) - _time.getMs() == 0)
        return (DEFAULT_TIMEOUT);
    if (static_cast<unsigned int>(time) - _time.getMs() > DEFAULT_TIMEOUT)
    return (DEFAULT_TIMEOUT);
    return (static_cast<unsigned int>(time) - _time.getMs());
}

typedef std::map<Packet, std::pair<unsigned long long, std::pair<ClassPtr *, FuncPtr> > > PoolMap;

    PoolMap         _pool;
    MyTime          _time;
    Protocol        *_proto;
};


#endif // TIMERPOOL_H
