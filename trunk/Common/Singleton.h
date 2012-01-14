#ifndef SINGLETON_H
#define SINGLETON_H

#include "Mutex.h"
#include "ScopedLock.h"

template <class T> class Singleton
{
public:
    static  T       *getInstance()
    {
        if (!_instance)
        {
            _createInstanceMut.lock();
            if (!_instance)
              _instance = new T();
            _createInstanceMut.unlock();
        }
        return (_instance);
    }

    static  void    deleteInstance()
    {
      if (_instance)
      {
          _createInstanceMut.lock();
        if (_instance)
            delete _instance;
        _instance = 0;
        _createInstanceMut.unlock();
       }
     }

private:
    Singleton();

    static T        *_instance;
    static Mutex    _createInstanceMut;
};

template <class T>
T *Singleton<T>::_instance = 0;

template <class T>
Mutex Singleton<T>::_createInstanceMut;

#endif // SINGLETON_H
