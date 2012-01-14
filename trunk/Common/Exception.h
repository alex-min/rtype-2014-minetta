#pragma once

#include <exception>
#include <string>

class Exception : public std::exception
{
  std::string	_msg;

 public :
  Exception(const std::string &) throw();
  virtual ~Exception() throw();
  virtual const char * what() const throw();
};
