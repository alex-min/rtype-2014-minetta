#ifndef POOL_H
#define POOL_H
#include <map>
#include "Singleton.h"
#include "Mutex.h"

template <class T> class PoolFactory {

public:
    typedef std::map<T *, bool> ListType;
    PoolFactory()
    {
        _createInstanceMut.create();
        _num_active = 0;
    }



    T *generate()
    {
        ScopedLock s(&_createInstanceMut);
        if (_num_active == 0)
        {
            T *a = new T();
            _active[a] = false;
            return a;
        }
        for (typename std::map<T *, bool>::iterator it = _active.begin(); it != _active.end(); ++it)
        {
            if (it->second == true)
            {
                it->first->erase();
                it->second = false;
                _num_active--;
                if (_num_active < 0)
                    _num_active = 0;
                return (it->first);
            }
        }
        T *a = new T();
        _active[a] = false;
        return (a);
    }


    template <class A>
    T *generate(A pa)
    {
        ScopedLock s(&_createInstanceMut);
        if (_num_active == 0)
        {
            T *a = new T(pa);
            _active[a] = false;
            return a;
        }
        for (typename std::map<T *, bool>::iterator it = _active.begin(); it != _active.end(); ++it)
        {
            if (it->second == true)
            {
                it->first->erase(pa);
                it->second = false;
                _num_active--;
                if (_num_active < 0)
                    _num_active = 0;
                return (it->first);
            }
        }
        T *a = new T(pa);
        _active[a] = false;
        return (a);
    }

    template <class A, class B>
    T *generate(A pa, B pb)
    {
        ScopedLock s(&_createInstanceMut);
        if (_num_active == 0)
        {
            T *a = new T(pa, pb);
            _active[a] = false;
            return a;
        }
        for (typename std::map<T *, bool>::iterator it = _active.begin(); it != _active.end(); ++it)
        {
            if (it->second == true)
            {
                it->first->erase(pa, pb);
                it->second = false;
                _num_active--;
                if (_num_active < 0)
                    _num_active = 0;
                return (it->first);
            }
        }
        T *a = new T(pa, pb);
        _active[a] = false;
        return (a);
    }


    void invalidate(T *a)
    {
        ScopedLock s(&_createInstanceMut);

        if (!a)
         a->invalidateEvent();
        _active[a] = true;
        _num_active++;
    }

    ListType const & getMapList() const {
        return (_active);
    }

    ListType & getMapList() {
        return (_active);
    }

protected:
    Mutex   _createInstanceMut;
    ListType _active;
    int _num_active;
};

// Usage : PoolSingleton(Packet *)::getInstance()->generate

#define PoolSingleton(a) Singleton< PoolFactory < a > >

#endif // POOL_H
