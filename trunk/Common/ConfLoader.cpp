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
}

ConfLoader::~ConfLoader()
{
  delete _file;
}

ConfObject const* ConfLoader::getConfObjectFor(std::string const &addr)
{
    std::map<std::string, ConfObject *>::iterator it;
    if ((it = _dico.find(addr)) != _dico.end())
    {
        return (it->second);
    }
    return (parseFile(addr));
}

bool ConfLoader::openFile(const std::string & file) 
{
  _file = new std::ifstream(file.c_str());
  return (!(_file->fail()));
}

ConfObject const*ConfLoader::parseFile(const std::string &path)
{
  std::string line;

  if (openFile(path) == false)
    throw Exception("Cannot open conf file");
  ConfObject *obj = new ConfObject(path);
  _dico[path] = obj;
  while ( ! _file->eof() )
    {
      getline((*_file), line);
      if (_file->bad())
          throw Exception("Cannot read Conf file");
      if (isLigneValide(line) == true)
        obj->putLineInDico(line);
    }
  return (obj);
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
