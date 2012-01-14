
#include "CUThread.h"

CUThread::CUThread(void)
  : _status(NOT_STARTED)
{
}

CUThread::~CUThread(void)
{
}

ThreadStatus CUThread::getStatus(void) const
{
  return (this->_status);
}

void CUThread::Start(void)
{
  int ret;

  ret = pthread_create(&this->_thread, NULL, &CUThread::exec, this);
  if (ret != 0)
    throw Exception("Can't create the thread.");
  if (!ret)
    this->_status = STARTED;
}

void CUThread::Exit(void)
{
  pthread_exit(NULL);
}

void CUThread::Join(void)
{
  int ret;

  ret = pthread_join(this->_thread, 0);
  if (ret != 0)
    throw Exception("Can't join the thread.");
  if (!ret)
    this->_status = DEAD;
}

void* CUThread::exec(void *data)
{
  CUThread *t;

  t = reinterpret_cast<CUThread *>(data);
  if (t)
    t->run();
  return (data);
}
