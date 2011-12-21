#ifndef ANIMATEDIMAGE_H
#define ANIMATEDIMAGE_H

#include "Image.h"
#include <list>

class AnimatedImage : public Image
{
public:
    AnimatedImage();
    AnimatedImage(std::string const &filename);
    bool    parseFile();
    std::list<sf::Sprite*>   const &getMonsters();
    virtual ~AnimatedImage();

private:
std::list<sf::Sprite*> _monsters;

protected:

};

#endif // ANIMATEDIMAGE_H
