#include "AnimatedImage.h"

AnimatedImage::AnimatedImage() : Image()
{
    _currentSprite = 0;
    _curTime = 0;
    _speed = 100;
    _rep = true;
    _done = false;
}

AnimatedImage::AnimatedImage(std::string const &filename) : Image(filename)
{
    _currentSprite = 0;
    _speed = 100;
    _rep = true;
    _done = false;
    _curTime = 0;
}

void            AnimatedImage::erase()
{
    _done = false;
    _curTime = 0;
}

void            AnimatedImage::setRepetition(bool rep)
{
    _rep = rep;
}

bool            AnimatedImage::isDone() const
{
    return (_done);
}

void    AnimatedImage::pinpointColumn(Int32 y, Int32 &beginX, Int32 beginY, Int32 &endX, Int32 &endY, bool &pixelOnLine, bool &pixelOnColumn)
{
    Int32 sizeX = _sprite.GetSize().x;

    endY = y;

    for (Int32 tmpX = 0; tmpX < sizeX; ++tmpX)
    {
        bool pixColumnTest = false;

        for (Int32 tmpY = beginY; tmpY < endY; ++tmpY)
        {
            if (_sprite.GetPixel(tmpX, tmpY).a != 0 && pixelOnColumn == false)
            {
                beginX = tmpX;
                pixelOnColumn = true;
            }

            if (_sprite.GetPixel(tmpX, tmpY).a != 0)
                pixColumnTest = true;
        }

        if (pixColumnTest == false && pixelOnColumn == true)
            pushInList(tmpX, beginX, beginY, endX, endY, pixelOnLine, pixelOnColumn);
    }
}

void    AnimatedImage::pushInList(Int32 tmpX, Int32 beginX, Int32 beginY, Int32 endX, Int32 endY, bool &pixelOnLine, bool &pixelOnColumn)
{
    endX = tmpX;

    sf::Sprite *sprite = new sf::Sprite(_image);

    sprite->SetSubRect(sf::Rect<int>(beginX, beginY, endX, endY));

    sprite->SetPosition(0, 0);

    _spriteList.push_back(sprite);

    pixelOnLine = false;
    pixelOnColumn = false;
}

bool    AnimatedImage::parseFile()
{
    if (_imageLoaded == false)
        return (false);

    Int32 sizeX = _sprite.GetSize().x;
    Int32 sizeY = _sprite.GetSize().y;
    Int32 beginY = 0;
    Int32 endY = 0;
    Int32 beginX = 0;
    Int32 endX = 0;
    bool pixelOnLine = false;
    bool pixelOnColumn = false;

    for (Int32 y = 0; y < sizeY; ++y)
    {
        bool pixLineTest = false;

        for (Int32 x = 0; x < sizeX; ++x)
        {
            if (_sprite.GetPixel(x, y).a != 0 && pixelOnLine == false)
            {
                beginY = y;
                pixelOnLine = true;
            }
            if (_sprite.GetPixel(x, y).a != 0)
                pixLineTest = true;
        }

        if (pixLineTest == false && pixelOnLine == true)
            pinpointColumn(y, beginX, beginY, endX, endY, pixelOnLine, pixelOnColumn);
    }

    _currentSprite = _spriteList.front();

    return (true);
}

sf::Sprite *AnimatedImage::getSpriteInList(UInt32 id)
{
    for (std::list<sf::Sprite*>::iterator it = _spriteList.begin(); it != _spriteList.end(); ++it)
        if (id-- == 0)
            return (*it);

    return (0);
}

sf::Sprite const *AnimatedImage::getSpriteInList(UInt32 id) const
{
    for (std::list<sf::Sprite*>::const_iterator it = _spriteList.begin(); it != _spriteList.end(); ++it)
        if (id-- == 0)
            return (*it);
    return (0);
}

void AnimatedImage::setCurrentSprite(UInt32 id)
{
    for (std::list<sf::Sprite*>::iterator it = _spriteList.begin(); it != _spriteList.end(); ++it)
        if (id-- == 0)
            _currentSprite = *it;

}

std::list<sf::Sprite*>   const &AnimatedImage::getSpriteList()
{
    return (_spriteList);
}

sf::Sprite  *AnimatedImage::getCurrentSprite()
{
    return (_currentSprite);
}

sf::Sprite  const *AnimatedImage::getCurrentSprite() const
{
    return (_currentSprite);
}

void    AnimatedImage::setCurrentSprite(sf::Sprite *currentSprite)
{
    _currentSprite = currentSprite;
}

void            AnimatedImage::update(UInt32 ms)
{
    _curTime += ms;
    if (_speed == 0) _speed = 40;
    UInt16 cur = _curTime / _speed;
    setCurrentSprite(getSpriteInList(cur));
    if (cur > getSpriteList().size() && _rep == false) {
        setCurrentSprite((sf::Sprite *) NULL);
        _done = true;
    }
    else {
    }
    if (_currentSprite == 0 && _rep)
    {
        setCurrentSprite(getSpriteInList(0));
        _curTime = 0;
    }
}

void            AnimatedImage::setSpeed(UInt32 speed)
{
    _speed = speed;
}

AnimatedImage::~AnimatedImage()
{

}
