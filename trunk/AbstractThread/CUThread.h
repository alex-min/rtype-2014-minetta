#pragma once

#include <pthread.h>
#include "IThread.h"
#include "../Network/Exception.h"

class CUThread : virtual public IThread
{
protected :
  pthread_t _thread;
  ThreadStatus _status;

  CUThread(const CUThread &);
  const CUThread & operator=(const CUThread &);

public:
  CUThread(void);
  virtual ~CUThread(void);

  ThreadStatus getStatus(void) const;
  void Start(void);
  void Join(void);

private :
  static void*	exec(void *);

protected:
  void Exit(void);
  virtual void run(void) = 0;
};

