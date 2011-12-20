#include "AnimatedImage.hpp"

AnimatedImage::AnimatedImage()
{
  _img = 0;
  _currentSprite = 0;
}

bool	AnimatedImage::loadFromFile(std::string const &filename)
{
  if (!Image.LoadFromFile("sprite.tga"))
    {
    }
}

AnimatedImage::~AnimatedImage()
{

}

