//
// ElfLoad.hpp for ff in /home/minett_a//Projets/tek2/nibbler/rendu/new/nibbler-2014-minett_a
// 
// Made by alexandre minette
// Login   <minett_a@epitech.net>
// 
// Started on  Wed Mar 16 11:15:35 2011 alexandre minette
// Last update Sat Mar 19 20:58:39 2011 joris profili
//

#ifndef ELFLOAD_H_
#define ELFLOAD_H_

#include <iostream>
#include <list>
#include <string>
#include <elf.h>
#include "utils.hpp"

typedef Elf32_Ehdr ElfHeader;
typedef Elf32_Shdr ElfSection;
typedef Elf32_Sym  ElfSymbol;
typedef Elf32_Phdr ElfProgram;

typedef Elf64_Ehdr ElfHeader64;
typedef Elf64_Shdr ElfSection64;
typedef Elf64_Sym  ElfSymbol64;
typedef Elf64_Phdr ElfProgram64;

class Elf32Load
{
public:
  Elf32Load();
  ~Elf32Load();
  void	dumpFile(std::string const &file);
  bool	isValidFile() const;
  const char	*getValidAddr(const char *addr) const;
  bool	getMasterSection();
  bool	getSectionList();
  bool	getStringTable();
  const char * getSectionName(const ElfSection *sec);
  bool	getSymbolStringTable();
  bool	getSymbolList();
  const char * getSymbolName(const ElfSymbol *sym);
  const std::list<const ElfSymbol *>  & extractSymbolList() const;

private:

  union {
    const char			   *_headerAddr;
    const ElfHeader			   *_header;
  };

  union {
    const ElfSection	*_masterSection;
    const char	*_masterSectionAddr;
  };

  const char *_maxAddr;
  unsigned int _fileSize;

  
  union {
    const ElfProgram	*_program;
    const char	*_programAddr;
  };

  const char	*_symbolStringTableAddr;
  const char	*_stringTableAddr;

  std::list<const ElfSection *> _sectionList;
  std::list<const ElfSymbol *> _symbolList;
};

#endif
