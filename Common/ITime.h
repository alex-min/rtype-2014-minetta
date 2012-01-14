#ifndef TIME_H
#define TIME_H

class ITime
{
public:
    virtual void setToMsTimeOfDay() = 0;
    virtual unsigned long long getMs() const = 0;
    virtual void setMs(unsigned long long ms) = 0;
};

#ifdef OS_WINDOWS
#include "windowstime.h"
typedef class Win32Time MyTime;
#elif defined OS_UNIX
#include "UNIXTime.h"
typedef class UNIXTime MyTime;
#endif

#endif // TIME_H
