#pragma once

#include "IMutex.h"
#include "../Network/Exception.h"
#include <pthread.h>

class CUMutex : public IMutex
{
protected:
  pthread_mutex_t mutex;

public:
  CUMutex(void);
  virtual ~CUMutex(void);

  virtual void lock(void);
  virtual void unlock(void);
  virtual bool trylock(void);
};

