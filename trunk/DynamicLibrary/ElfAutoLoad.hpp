//
// ElfAutoLoad.hpp for ff in /home/minett_a//Projets/tek2/nibbler/rendu/new/nibbler-2014-minett_a
// 
// Made by alexandre minette
// Login   <minett_a@epitech.net>
// 
// Started on  Thu Mar 17 13:02:07 2011 alexandre minette
// Last update Sat Mar 19 20:40:18 2011 joris profili
//

#ifndef ELFAUTOLOAD_H_
#define ELFAUTOLOAD_H_

#include <string>
#include <list>
#include "ElfLoad.hpp"
#include "baseRegex.hpp"

class ElfAutoLoad
{
public:
  ElfAutoLoad();
  ~ElfAutoLoad();
  void	dumpFile(std::string const &file);
  std::list<const char *> getSymbolsFromRegex(const char *regex);

private:
  Elf32Load	_elf;
};

#endif
