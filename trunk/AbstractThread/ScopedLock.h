#pragma once

template <typename X>
class ScopedLock
{
  X & _var;

  ScopedLock(const X &);
  ScopedLock<X>& operator=(const ScopedLock<X> &);
public :
  ScopedLock(X & var)
    : _var(var)
  {
    this->_var.lock();
  }

  ~ScopedLock(void)
  {
    this->_var.unlock();
  }
};
