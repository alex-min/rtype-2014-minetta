//
// ElfLoad.cpp for ff in /home/minett_a//Projets/tek2/nibbler/rendu/new/nibbler-2014-minett_a
// 
// Made by alexandre minette
// Login   <minett_a@epitech.net>
// 
// Started on  Wed Mar 16 11:15:12 2011 alexandre minette
// Last update Sat Mar 19 20:58:49 2011 joris profili
//

#include "ElfLoad.hpp"

Elf32Load::Elf32Load() :
  _header(NULL),
  _masterSection(NULL),
  _maxAddr(NULL),
  _fileSize(0),
  _program(NULL),
  _symbolStringTableAddr(NULL),
  _stringTableAddr(NULL)
{
}

Elf32Load::~Elf32Load()
{
}

const char	*Elf32Load::getValidAddr(const char *addr) const
{
  if (!_header || addr < _headerAddr || addr >= _maxAddr)
    return (0);
  return (addr);    
}

bool	Elf32Load::getMasterSection()
{
  if (_headerAddr == NULL || _header->e_shoff == 0)
    return (false);
  _masterSectionAddr = Elf32Load::getValidAddr(_headerAddr + _header->e_shoff);
  if (!_masterSectionAddr)
    return (false);
  return (true);
}

bool	Elf32Load::getSectionList()
{
  if (_header == NULL || _masterSectionAddr == NULL)
    return (false);
  for (int i = 1; i < _header->e_shnum; ++i)
    if (getValidAddr(reinterpret_cast<const char *> (_masterSection + i)))
      _sectionList.push_back(_masterSection + i);
  return (true);
}

bool	Elf32Load::getStringTable()
{
  if (_header == NULL || _masterSection == NULL)
    return (false);
  _stringTableAddr = NULL;
  if (!getValidAddr(reinterpret_cast<const char *> (_masterSection + _header->e_shstrndx)))
    return (false);
  _stringTableAddr = getValidAddr(reinterpret_cast<const char *> (_headerAddr
	+ _masterSection[_header->e_shstrndx].sh_offset));
  if (!_stringTableAddr)
    return (false);
  return (true);
}

const char * Elf32Load::getSectionName(const ElfSection *sec)
{
  if (_header == NULL || _stringTableAddr == NULL || sec == NULL || !(sec->sh_name))
    return (NULL);
  return (getValidAddr(_stringTableAddr + sec->sh_name));
}

bool	Elf32Load::getSymbolStringTable()
{
  if (_header == NULL || _masterSection == NULL)
    return (false);
  for (std::list<const ElfSection *>::iterator it = _sectionList.begin();
       it != _sectionList.end(); ++it)
    {
      const char *name = Elf32Load::getSectionName(*it);
      if (name && !Utils::my_strcmp(name, ".strtab"))
	{
	  _symbolStringTableAddr = getValidAddr(_headerAddr + (*it)->sh_offset);
	  if (_symbolStringTableAddr)
	    return (true);
	}
    }
  return (false);
}

bool	Elf32Load::getSymbolList()
{
  const ElfSymbol *sym;
  size_t	symbol_count;
  size_t	j;

  if (_header == NULL || _masterSection == NULL)
    return (false);
  for (std::list<const ElfSection *>::iterator it = _sectionList.begin();
       it != _sectionList.end(); ++it)
    {
      if (*it && (*it)->sh_type == SHT_SYMTAB)
	{
	  sym = reinterpret_cast<const ElfSymbol *> (getValidAddr(_headerAddr + (*it)->sh_offset));
	  symbol_count = (*it)->sh_size / sizeof(ElfSymbol);
	  for (j = 1; sym && j < symbol_count && j >= 1; ++j)
	    _symbolList.push_back(sym + j);
	}
    }
  return (true);
}

const char * Elf32Load::getSymbolName(const ElfSymbol *sym)
{
  if (!_headerAddr || !_symbolStringTableAddr)
    return (NULL);
  return (getValidAddr(_symbolStringTableAddr + sym->st_name));
}

const std::list<const ElfSymbol *>  & Elf32Load::extractSymbolList() const
{
  return (_symbolList);
}

void	Elf32Load::dumpFile(std::string const &file)
{
  _headerAddr = Utils::dumpFile(file, &_fileSize);
  _maxAddr = _headerAddr + _fileSize;
  if (!isValidFile())
    return ;
  getMasterSection();
  getSectionList();
  getStringTable();
  getSymbolStringTable();
  getSymbolList();
}

bool	Elf32Load::isValidFile() const
{
  int	i;

  if (_fileSize <= SELFMAG)
    return (false);
  for (i = 0; i < SELFMAG; ++i)
    {
      if (_headerAddr[i] != ELFMAG[i])
	return (false);
    }
  return (true);
}
