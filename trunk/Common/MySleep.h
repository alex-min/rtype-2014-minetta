#ifndef MYSLEEP_H
#define MYSLEEP_H

#ifdef OS_UNIX
#include <unistd.h>
#define MySleepMs(num) ::usleep((num) * 1000)
#elif defined OS_WINDOWS
#error "MySleep.h : MySleepMs not implemented on windows platform"
#else
#error "MySleep.h : MySleepMs is not implemented for your vendor platform"
#endif

#endif // MYSLEEP_H
