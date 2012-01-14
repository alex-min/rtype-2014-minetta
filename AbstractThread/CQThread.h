#pragma once

#include "IThread.h"
#include <QThread>

class CQThread : virtual public IThread, public QThread
{
    ThreadStatus _status;

    CQThread(const CQThread &);
     const CQThread & operator=(const CQThread &);
public:
    CQThread();
    virtual ~CQThread(void);

    virtual ThreadStatus getStatus(void) const;
    virtual void Start(void);
    virtual void Join(void);

protected:
    virtual void Exit(void);
    virtual void run(void) = 0;
};

