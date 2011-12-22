#ifndef TIMER_H_
#define TIMER_H_

#include "SystemDefines.h"

class	Timer
{
public:
  Timer();  
  void		setTime(Uint32 ms);
  UInt32	getTime() const;
  bool		subTime(Uint32 gameTime);
  bool		isDone() const;
  void		sleepDifference(void);
  ~Timer();

private:

  UInt32	_curTime;
  UInt32	_initTime;
  bool		_done;
};

#endif
