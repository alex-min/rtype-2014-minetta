#include "APlayer.h"

APlayer::APlayer() :

    _speed(0.0),
    _sprite(0),
    _isDead(false),
    _shoot(false),
    _available(true),
    _screenWidth(0),
    _screenHeight(0),
    _origin(PointF(0, -1))
{
    _expW = 0;
    _expH = 0;
    _explosionSprite = NULL;
    _backSprite = 0;
}

void    APlayer::setAvailibility(bool available)
{
    _available = available;
}

bool     APlayer::isAvailable() const
{
    return (_available);
}

bool            APlayer::getShoot() const
{
    return (_shoot);
}

void          *APlayer::getSprite()
{
    return (_sprite);
}

UInt32              APlayer::getScreenWidth() const
{
    return (_screenWidth);
}

UInt32              APlayer::getScreenHeight() const
{
    return (_screenHeight);
}

void                APlayer::setExplosionSprite(void *sprite, float imgWidth, float imgHeight)
{
    _explosionSprite = sprite;
    _expW = imgWidth;
    _expH = imgHeight;
}

void                APlayer::resetSprites()
{
    if (_backSprite) {
     _sprite = _backSprite;
        _w = _expWB;
        _h = _expHB;
    }
}

void                APlayer::switchToExplosionSprite()
{
    _sprite = _explosionSprite;
    _w = _expW;
    _h = _expH;
}

void                APlayer::setSprite(void *sprite, float imgWidth, float imgHeight)
{
    _sprite = sprite;

    _w = imgWidth;
    _h = imgHeight;
    _backSprite = sprite;
    _expWB = _w;
    _expHB = _h;
}

APlayer::~APlayer()
{

}

double        APlayer::getSpeed()
{
    return (_speed);
}

void                APlayer::setSpeed(double speed)
{
    _speed = speed;
}

void                APlayer::die()
{
    _isDead = true;
}

bool                APlayer::isDead()
{
    return (_isDead);
}

void                APlayer::spawn(const Point<float> &origine)
{
    _pos = origine;
    _isDead = false;
}

float        APlayer::getSpriteWidth()
{
    return (_w);
}

void                APlayer::erase()
{
    _w = 0;
    _h = 0;
    _speed = 0;
    _isDead = false;
    _shoot = false;
    _available = true;
  //  _sprite = 0;
    _pos.setCoord(-200, 0);
}

void                APlayer::setOrigin(Point<float> const &origin)
{
    _origin = origin;
}

float        APlayer::getSpriteHeight()
{
    return (_h);
}

void                APlayer::setSize(float width, float height)
{
    _w = width;
    _h = height;
}

void                APlayer::setScreenSize(UInt32 screenWidth, UInt32 screenHeight)
{
    _screenWidth = screenWidth;
    _screenHeight = screenHeight;
}
