#include "Exception.h"

Exception::Exception(const std::string &msg) throw()
  : _msg(msg)
{
}

Exception::~Exception() throw()
{
}

const char * Exception::what() const throw()
{
  return (this->_msg.c_str());
}
