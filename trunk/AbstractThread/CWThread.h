#pragma once

#include <Windows.h>
#include "IThread.h"

class CWThread : virtual public IThread
{
    HANDLE _thread;
    ThreadStatus _status;

    CWThread(const CWThread &);
     const CWThread & operator=(const CWThread &);

   public:
     CWThread(void);
     virtual ~CWThread(void);

     ThreadStatus getStatus(void) const;
     void Start(void);
     void Join(void);

   private :
     static DWORD    exec(void *);

   protected:
     void Exit(void);
     virtual void run(void) = 0;
};
