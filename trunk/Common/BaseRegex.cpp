//
// baseRegex.cpp for ff in /home/minett_a//Projets/tek2/abstractVM/tests/rx2
// 
// Made by alexandre minette
// Login   <minett_a@epitech.net>
// 
// Started on  Mon Feb 14 09:22:31 2011 alexandre minette
// Last update Wed Mar 16 11:07:08 2011 alexandre minette
//

#include "BaseRegex.h"

bool BaseRegex::range(const char *range, char test)
{
  char a, b;

  if (!range)
    return (false);
  if (*range != '[')
    return (false);
  ++range;
  if (!*range)
    return (false);
  a = *range;
  ++range;
  if (!*range || *range != '.')
    return (false);
  ++range;
  if (!*range || *range != '.')
    return (false);
  ++range;
  b = *range;
  if (!*range)
    return (false);
  ++range;
  if (!*range || *range != ']')
    return (false);
  if (test >= a && test <= b)
    return (true);
  return (false);
}

void	BaseRegex::pt(const char **str, int *pos, int *contig_pos,
		      const char **contig_ptr, const char *rx)
{
  const char *tmp;

  ++(*str);
  ++(*pos);
  *contig_ptr = *str;
  *contig_pos = *pos;
  tmp = rx + 1;
  if (*tmp == '*' || *tmp == '+')
    {
      ++tmp;
      while (*tmp != **contig_ptr && *rx && **contig_ptr)
	{
	  ++(*contig_pos);
	  ++(*contig_ptr);
	}
    }
}

bool	BaseRegex::c_range(const char **str, int *pos, int *contig_pos,
		      const char **contig_ptr, const char *rx)
{
  bool failed = false;

  if (range(rx, **str))
    {
      ++(*str);
      ++(*pos);
    }	  
  else
    failed = true;
  (*contig_ptr) = (*str);
  (*contig_pos) = (*pos);
  while (range(rx, *(*contig_ptr)) && *rx)
    {
      ++(*contig_pos);
      ++(*contig_ptr);
    }
  return (failed);
}

bool BaseRegex::base_char(const char **str, int *pos, int *contig_pos,
	       const char **contig_ptr, const char *rx)
{
  bool failed = false;

  if (*rx == *(*str))
    {
      ++(*str);
      ++(*pos);
    }
  else
    failed = true;
  (*contig_ptr) = (*str);
  (*contig_pos) = (*pos);
  while (*rx == *(*contig_ptr) && *rx && *(*contig_ptr))
    {
      ++(*contig_pos);
      ++(*contig_ptr);
    }
  return (failed);
}

int BaseRegex::match(const char *rx, const char *str)
{
  int pos = 0;
  int contig_pos = 0;
  const char *contig_ptr;
  bool failed = false;

  while (*rx)
    {
      if (!(*str))
	return (0);
      switch (*rx)
	{
	case '*':
	  failed = false;
	  pos = contig_pos;
	  str = contig_ptr;
	  break;
	case '+':
	  pos = contig_pos;
	  str = contig_ptr;
	  break;
	case '?':
	  failed = false;
	  break;
	case '[':
	  if (failed)
	    return (0);
	  if (c_range(&str, &pos, &contig_pos, &contig_ptr, rx))
	    failed = true;
	  while (*rx && *rx != ']')
	    ++rx;
	  break;
	case '.':
	  if (failed)
	    return (0);
	  pt(&str, &pos, &contig_pos, &contig_ptr, rx);
	  break;
	case '\\':
	  ++rx;
	default:
	  if (failed)
	    return (0);
	  if (base_char(&str, &pos, &contig_pos, &contig_ptr, rx))
	    failed = true;
	  break;
	}
      ++rx;
    }
  return ((failed) ? 0 : pos);
}
