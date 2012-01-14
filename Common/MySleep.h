#ifndef MYSLEEP_H
#define MYSLEEP_H

#ifdef OS_UNIX
#include <unistd.h>
#define MySleepMs(num) ::usleep((num) * 1000)
#elif defined OS_WINDOWS
#define MySleepMs(num) ::Sleep(num)
#else
#error "MySleep.h : MySleepMs is not implemented for your vendor platform"
#endif

#endif // MYSLEEP_H
