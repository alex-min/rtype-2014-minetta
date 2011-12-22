#pragma once

#include <QMutex>
#include "IMutex.h"

class CQMutex : public IMutex
{
    QMutex  _mutex;
public:
    CQMutex();
    virtual ~CQMutex(void);
    virtual void lock(void);
    virtual void unlock(void);
    virtual bool trylock(void);
};

