#include <iostream>

#define SONGPATH   ("../songs/")

class	ISounds
{
public:
  virtual ~ISounds() {}
  virtual void	playSound(const std::string &soundname) = 0;
  virtual void	pauseSound(const std::string &soundname) = 0;
  virtual void	stopSound(const std::string &soundname) = 0;
};
