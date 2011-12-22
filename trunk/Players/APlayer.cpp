#include "APlayer.h"

APlayer::APlayer(double speed, void *sprite, bool isDead) :

    _speed(speed),
    _sprite(sprite),
    _isDead(isDead)
{

}

void          *APlayer::getSprite()
{
    return (_sprite);
}

void                APlayer::setSprite(void *sprite, float imgWidth, float imgHeight)
{
    _sprite = sprite;

    _w = imgWidth;
    _h = imgHeight;
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
    _isDead = true;
    _sprite = 0;
    _pos.setCoord(0, 0);
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
