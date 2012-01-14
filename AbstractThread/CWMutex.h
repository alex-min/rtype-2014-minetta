#pragma once

#include "Windows.h"
#include "IMutex.h"

class CWMutex : public IMutex
{
    CRITICAL_SECTION _mutex;

public :
    CWMutex(void);
    virtual ~CWMutex(void);

    virtual void lock(void);
    virtual void unlock(void);
    virtual bool trylock(void);
};

