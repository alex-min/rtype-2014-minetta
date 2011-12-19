//
// ConfLoader.hpp for  in /home/bastie_v//projet/bomberman
// 
// Made by valentin bastien
// Login   <bastie_v@epitech.net>
// 
// Started on  Fri Jun  3 11:38:16 2011 valentin bastien
// Last update Fri Jun  3 12:45:13 2011 valentin bastien
//

#ifndef __CONFLOADER_HPP__
#define __CONFLOADER_HPP__

#include <iostream>
#include <fstream>
#include <map>
#include "Exception.h"

class ConfLoader
{
public:

  static ConfLoader *getInstance();
  static void kill();
  void parseFile();
  std::string const &getStringValueOf(std::string const &key) const;
private:

  ConfLoader();
  ~ConfLoader();
  bool openFile(const std::string &file = "./conf");
  bool isLigneValide(const std::string &ligne) const;
  void putLineInDico(std::string const &str);
  std::ifstream *_file;
  static ConfLoader *_loader;
  std::map<std::string, std::string> _dico;
};
#endif
