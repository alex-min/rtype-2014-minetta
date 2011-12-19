#ifndef APLAYER_H
#define APLAYER_H

#include "IPlayer.h"

class APlayer : public IPlayer
{
public:
    APlayer();
    virtual const AnimatedSprite          *getSprite();
    virtual void                setSprite(AnimatedSprite *sprite, unsigned int imgWidth, unsigned int imgHeight);
    virtual unsigned int        getSpeed();
    // Speed en pixel/ms
    virtual void                setSpeed(int speed);
    virtual Point<int> const    &getPosition();
    virtual void                die();
    virtual bool                isDead();
    virtual bool                spawn(const Point<int> &);
    virtual unsigned int        getSpriteWidth();
    virtual void                erase();
    virtual unsigned int        getSpriteHeight();
    virtual void                setPixelSize(unsigned int width, unsigned int height);
    virtual bool                setPosition(Point<int> const &);
    virtual ~APlayer();
protected:
    int                         _speed;
    Point<int>                  _position;
    AnimatedSprite              *_sprite;
    bool                        _isDead;
    unsigned int                _widthSize;
    unsigned int                _heightSize;
};

#endif // APLAYER_H
