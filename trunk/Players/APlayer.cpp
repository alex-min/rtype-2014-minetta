#include "APlayer.h"

APlayer::APlayer(double speed) : _speed(speed), _position(Point<int>(0,0)), _sprite(0), _isDead(0), _widthSize(0), _heightSize(0)
{
}

const AnimatedSprite          *APlayer::getSprite()
{
    return (_sprite);
}

void                APlayer::setSprite(AnimatedSprite *sprite, unsigned int imgWidth, unsigned int imgHeight)
{
    _sprite = sprite;
    _widthSize = imgWidth;
    _heightSize = imgHeight;
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

Point<int> const    &APlayer::getPosition()
{
    return (_position);
}

void                APlayer::die()
{
     _isDead = true;
}

bool                APlayer::isDead()
{
    return (_isDead);
}

bool                APlayer::spawn(const Point<int> &origine)
{
    _position = origine;
    return (true);
}

unsigned int        APlayer::getSpriteWidth()
{
    return (_widthSize);
}

void                APlayer::erase()
{
    _widthSize = 0;
    _heightSize = 0;
    _speed = 0;
    _isDead = true;
    _sprite = 0;
}

unsigned int        APlayer::getSpriteHeight()
{
    return (_heightSize);
}

void                APlayer::setPixelSize(unsigned int width, unsigned int height)
{
    _widthSize = width;
    _heightSize = height;
}

bool                APlayer::setPosition(Point<int> const &origine)
{
    _position = origine;
    return (true);
}
