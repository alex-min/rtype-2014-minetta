//
// Timer.cpp for ff in /home/minett_a//Projets/tek2/bombermann/tp
// 
// Made by alexandre minette
// Login   <minett_a@epitech.net>
// 
// Started on  Sat Apr 30 09:34:17 2011 alexandre minette
// Last update Thu Jun  2 12:21:23 2011 alexandre minette
//

#include <iostream>
#include "Timer.h"

Timer::Timer() :
  _curTime(0),
  _initTime(0)
{
}

void	Timer::setTime(UInt32 ms)
{
  _curTime = 0;
  _initTime = ms;
}

UInt32	Timer::getTime() const
{
  return (_initTime);
}

bool	Timer::subTime(UInt32 gameTime)
{
  _curTime += gameTime;
  if (_curTime >= _initTime)
    {
      _curTime = 0;
      _done = true;
      return (true);
    }
  return (false);
}

Timer::~Timer()
{

}
