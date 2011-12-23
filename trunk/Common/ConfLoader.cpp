//
// ConfLoader.cpp for  in /home/bastie_v//projet/bomberman
// 
// Made by valentin bastien
// Login   <bastie_v@epitech.net>
// 
// Started on  Fri Jun  3 11:38:18 2011 valentin bastien
// Last update Fri Jun  3 17:10:19 2011 joris profili
//

#include "ConfLoader.hpp"

ConfLoader *ConfLoader::_loader = NULL;

ConfLoader::ConfLoader()
{
  _loader = NULL;
  if (openFile() == false)
    throw Exception("Cannot open conf file");
  parseFile();
}

ConfLoader::~ConfLoader()
{
  delete _file;
}

bool ConfLoader::openFile(const std::string & file) 
{ 
  _file = new std::ifstream(file.c_str());
  return (!(_file->fail()));
} 

std::string const &ConfLoader::getStringValueOf(std::string const &key) const
{
  std::map<std::string, std::string>::const_iterator it;

  for (it = _dico.begin(); it != _dico.end(); ++it)
    {
      if ((*it).first.compare(key) == 0)
	return ((*it).second);
    }
  throw Exception("Cannot find " + key + " in conf file");
}

void ConfLoader::putLineInDico(std::string const &str)
{
  std::string key;
  std::string value;
  int sep;

  sep = str.find('=', 0);
  key = str.substr(0, sep);
  value = str.substr(sep + 1);
  _dico[key] = value;
}

void ConfLoader::parseFile()
{
  std::string line;

  while ( ! _file->eof() )
    {
      getline((*_file), line);
      if (_file->bad())
          throw Exception("Cannot read Conf file");
      if (isLigneValide(line) == true)
	putLineInDico(line);
    }
}

ConfLoader *ConfLoader::getInstance()
{
  if (_loader == NULL)
    _loader = new ConfLoader();
  return (_loader);
}

void ConfLoader::kill()
{
  if (_loader != NULL)
    {
      delete _loader;
      _loader = NULL;
    }
}

bool ConfLoader::isLigneValide(const std::string &ligne) const
{
  size_t pos;

  pos = ligne.find('=', 0);
  if (pos != std::string::npos && pos < ligne.length() - 1 && pos > 0)
    return (true);
  return (false);
}
