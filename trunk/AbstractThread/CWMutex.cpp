#include "CWMutex.h"

CWMutex::CWMutex(void)
{
    InitializeCriticalSection(&_mutex);
}

CWMutex::~CWMutex(void)
{
    DeleteCriticalSection(&_mutex);
}

void	CWMutex::lock(void)
{
    EnterCriticalSection(&_mutex);
}

void	CWMutex::unlock(void)
{
    LeaveCriticalSection(&_mutex);
}

bool	CWMutex::trylock(void)
{
  int	ret;

  ret = TryEnterCriticalSection(&_mutex);
  if (!ret)
    return (false);
  return (true);
}
