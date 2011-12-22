
#include "CUMutex.h"

CUMutex::CUMutex(void)
{
  if (pthread_mutex_init(&this->mutex, NULL) != 0)
    throw Exception("Mutex can't be create.");
}

CUMutex::~CUMutex(void)
{
  if (pthread_mutex_destroy(&this->mutex) != 0)
    throw Exception("Mutex can't be destroy.");
}

void	CUMutex::lock(void)
{
  if (pthread_mutex_lock(&this->mutex) != 0)
    throw Exception("Mutex can't be lock.");

}

void	CUMutex::unlock(void)
{
  if (pthread_mutex_unlock(&this->mutex) != 0)
    throw Exception("Mutex can't be unlock.");
}

bool	CUMutex::trylock(void)
{
  int	ret;

  ret = pthread_mutex_trylock(&this->mutex);
  if (ret)
    return (false);
  return (true);
}
