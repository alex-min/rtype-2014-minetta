#ifndef ANIMATEDIMAGE_H
#define ANIMATEDIMAGE_H

#include "Image.h"
#include <list>
#include "SystemDefines.h"

class AnimatedImage : public Image
{
public:
    AnimatedImage();
    AnimatedImage(std::string const &filename);
    bool    parseFile();
    std::list<sf::Sprite*>   const &getSpriteList();
    sf::Sprite *getSpriteInList(UInt32 id);
    sf::Sprite const *getSpriteInList(UInt32 id) const;
    sf::Sprite  *getCurrentSprite();
    sf::Sprite  const *getCurrentSprite() const;
    void                setCurrentSprite(sf::Sprite *currentSprite);
    virtual ~AnimatedImage();

private:
    void    pinpointColumn(Int32 y, Int32 &beginX, Int32 beginY, Int32 &endX, Int32 &endY, bool &pixelOnLine, bool &pixelOnColumn);
    void    pushInList(Int32 tmpX, Int32 beginX, Int32 beginY, Int32 endX, Int32 endY, bool &pixelOnLine, bool &pixelOnColumn);

private:
std::list<sf::Sprite*> _spriteList;
sf::Sprite            *_currentSprite;

protected:

};

#endif // ANIMATEDIMAGE_H
