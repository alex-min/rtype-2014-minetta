#include "CQThread.h"

CQThread::CQThread()
  : _status(NOT_STARTED)
{
}

CQThread::~CQThread(void)
{
}

ThreadStatus CQThread::getStatus(void) const
{
    return (this->_status);
}

void CQThread::Start(void)
{
    this->start();
    this->_status = STARTED;
}

void CQThread::Exit(void)
{
    this->quit();
}

void CQThread::Join(void)
{
    this->wait();
    this->_status = DEAD;
}
