//
// baseRegex.hpp for fff in /home/minett_a//Projets/tek2/abstractVM/tests/rx2
// 
// Made by alexandre minette
// Login   <minett_a@epitech.net>
// 
// Started on  Mon Feb 14 09:21:22 2011 alexandre minette
// Last update Fri Feb 18 21:23:50 2011 alexandre minette
//

#ifndef BASEREGEX_H_
#define BASEREGEX_H_

#include <list>



class BaseRegex
{
public:
  static bool c_range(const char **str, int *pos, int *contig_pos,
		      const char **contig_ptr, const char *rx);
  static void pt(const char **str, int *pos, int *contig_pos,
	    const char **contig_ptr, const char *rx);
  static bool base_char(const char **str, int *pos, int *contig_pos,
	    const char **contig_ptr, const char *rx);
  static void match_char(int *contig_pos,
			 const char **contig_ptr,
			 bool *failed,
			 const char *rx,
			 const char **str);
  static bool range(const char *range, char test);
  static int match(const char *rx, const char *str);
};

#endif
