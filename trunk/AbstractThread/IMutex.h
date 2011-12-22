#pragma once

class IMutex
{
public :
  virtual ~IMutex(void) {}
  virtual void lock(void) = 0;
  virtual void unlock(void) = 0;
  virtual bool trylock(void) = 0;
};

#ifdef _WIN32
    #include "CWMutex.h"
    #define MUTEX CWMutex
#else
    #include "CUMutex.h"
    #define MUTEX CUMutex
#endif
