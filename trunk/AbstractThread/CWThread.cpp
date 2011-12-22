#include "CWThread.h"

CWThread::CWThread(void)
  : _status(NOT_STARTED)
{
}

CWThread::~CWThread(void)
{
}

ThreadStatus CWThread::getStatus(void) const
{
  return (this->_status);
}

void CWThread::Start(void)
{
  _thread = CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(&CWThread::exec), this, 0, NULL);
  if (!_thread)
    throw Exception("Can't create the thread.");
  this->_status = STARTED;
}

void CWThread::Exit(void)
{
    TerminateThread(_thread, 0);
}

void CWThread::Join(void)
{
  WaitForSingleObject(_thread, INFINITE);
  this->_status = DEAD;
}

DWORD CWThread::exec(void *data)
{
  CWThread *t;

  t = reinterpret_cast<CWThread *>(data);
  if (t)
    t->run();
  return (0);
}

