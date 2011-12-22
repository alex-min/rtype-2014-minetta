#include "WinDynaLib.hpp"

WinDynaLib::WinDynaLib()
{
}

void    WinDynaLib::dynaLoad(std::string libName)
{
    wchar_t *name = this->convertStringToWchar(libName);
    _DLLHandle = LoadLibrary(name);
    if (_DLLHandle == NULL)
        throw new Exception("can't load the specified dll");
}

void    *WinDynaLib::funcLoad(std::string funcName)
{
    if (_DLLHandle != NULL)
        return((void *)GetProcAddress(_DLLHandle, funcName.c_str()));
    throw new Exception("can't find the specified function");
    return (0);
}

void    WinDynaLib::dynaFree()
{
    FreeLibrary(_DLLHandle);
}

unsigned int	WinDynaLib::getWcharSize(const wchar_t *s)
{
  unsigned int i = 0;

  for (i = 0; s[i]; i++);
  return (i);
}

wchar_t	*WinDynaLib::convertStringToWchar(std::string const &s)
{
  wchar_t *convertedString = new wchar_t[s.size() + 1];

  for (unsigned int i = 0; i < s.size() + 1; i++)
    convertedString[i] = '\0';
  mbstowcs(convertedString, s.c_str(), s.size());

  return (convertedString);
}

std::string	WinDynaLib::convertWcharToString(const wchar_t *s)
{
  char *convertedString = new char[getWcharSize(s) + 1];
  std::string ret;
  for (unsigned int i = 0; i < getWcharSize(s) + 1; i++)
    convertedString[i] = '\0';
  wcstombs(convertedString, s, getWcharSize(s));
  ret = convertedString;
  delete convertedString;

  return (ret);
}
