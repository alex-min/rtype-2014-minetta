#include "Sfml.h"
#include "ISounds.h"

class	Sounds : public ISounds
{
public:
  Sounds(const std::string &music, const std::string &weapon, const std::string &explosion);
  virtual ~Sounds();
  void		playSound(const std::string &soundname);
  void		pauseSound(const std::string &soundname);
  void		stopSound(const std::string &soundname);
  sf::Sound::Status   getStatusOf(std::string const &soundName);

 private:
  sf::Music	_gameMusic;
  sf::Music	_weaponFire;
  sf::Music	_explosion;
};
