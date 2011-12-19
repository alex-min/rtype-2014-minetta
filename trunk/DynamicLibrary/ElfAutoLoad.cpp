//
// ElfAutoLoad.cpp for ff in /home/minett_a//Projets/tek2/nibbler/rendu/new/nibbler-2014-minett_a
// 
// Made by alexandre minette
// Login   <minett_a@epitech.net>
// 
// Started on  Thu Mar 17 13:01:49 2011 alexandre minette
// Last update Sat Mar 19 20:40:25 2011 joris profili
//

#include "ElfAutoLoad.hpp"

ElfAutoLoad::ElfAutoLoad()
{
}

ElfAutoLoad::~ElfAutoLoad()
{
}

void	ElfAutoLoad::dumpFile(std::string const &file)
{
  _elf.dumpFile(file);
}


std::list<const char *> ElfAutoLoad::getSymbolsFromRegex(const char *regex)
{
  std::list<const char *> list;

  const std::list<const ElfSymbol *> & symList = _elf.extractSymbolList();
  for (std::list<const ElfSymbol *>::const_iterator it = symList.begin();
       it != symList.end(); ++it)
    {
      if (BaseRegex::match(regex, _elf.getSymbolName(*it)))
	{
	  list.push_back(_elf.getSymbolName(*it));
	}
    }
  return (list);
}
