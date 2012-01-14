#include "Sounds.h"

Sounds::Sounds(const std::string &music, const std::string &weapon, const std::string &explosion)
{
    if (!_gameMusic.OpenFromFile(std::string(SONGPATH) + music))
        std::cout << "Error trying to open the music song file -> " <<  std::string(SONGPATH) + music << std::endl;
    else
        _gameMusic.SetLoop(true);
    if (!_weaponFire.OpenFromFile(std::string(SONGPATH) + weapon))
        std::cout << "Error trying to open the weapon song file -> " << std::string(SONGPATH) + weapon << std::endl;
    else
        _weaponFire.SetLoop(true);
    if (!_explosion.OpenFromFile(std::string(SONGPATH) + explosion))
        std::cout << "Error trying to open the explosion file -> " << std::string(SONGPATH) + explosion << std::endl;
}

sf::Sound::Status   Sounds::getStatusOf(std::string const &soundName)
{
    sf::Sound::Status status = sf::Sound::Stopped;

    if (soundName == "music")
        status = _gameMusic.GetStatus();
    else if (soundName == "missil")
        status = _weaponFire.GetStatus();
    else
        status = _explosion.GetStatus();

    return (status);
}

Sounds::~Sounds()
{

}

void	Sounds::playSound(const std::string &soundname)
{
    if (soundname == "music")
        _gameMusic.Play();
    else if (soundname == "missil")
        _weaponFire.Play();
    else
        _explosion.Play();
}

void	Sounds::pauseSound(const std::string &soundname)
{
    if (soundname == "music")
        _gameMusic.Pause();
    else if (soundname == "missil")
        _weaponFire.Pause();
    else
        _explosion.Pause();
}

void	Sounds::stopSound(const std::string &soundname)
{
    if (soundname == "music")
        _gameMusic.Stop();
    else if (soundname == "missil")
        _weaponFire.Stop();
    else
        _explosion.Stop();
}
