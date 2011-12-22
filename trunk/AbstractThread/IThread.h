#pragma once

#include <iostream>
#include "../Network/Exception.h"

enum ThreadStatus
  {
    NOT_STARTED,
    STARTED,
    DEAD
  };

class IThread
{
public:
  virtual ~IThread(void) {}

  virtual ThreadStatus getStatus(void) const = 0;
  virtual void Start(void) = 0;
  virtual void Join(void) = 0;

protected:
  virtual void Exit(void) = 0;
  virtual void run(void) = 0;
};

#ifdef _WIN32
    #include "CWThread.h"
    #define THREAD CWThread
#else
    #include "CUThread.h"
    #define THREAD CUThread
#endif
