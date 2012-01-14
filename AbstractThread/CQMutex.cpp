#include "CQMutex.h"

CQMutex::CQMutex()
{
}

CQMutex::~CQMutex(void)
{
}

void	CQMutex::lock(void)
{
    _mutex.lock();
}

void	CQMutex::unlock(void)
{
    _mutex.unlock();
}

bool	CQMutex::trylock(void)
{
  int	ret;

  ret = _mutex.tryLock();
  return (ret);
}
