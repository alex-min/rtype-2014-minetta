#ifndef IPLAYER_H
#define IPLAYER_H

#include "AnimatedSprite.h"
#include "Common/Point.h"

class IPlayer
{
public:
    enum Direction{
        LEFT,
        RIGHT,
        UP,
        DOWN,
        UNKNOWN
    };
    virtual const AnimatedSprite *getSprite() = 0;
    virtual void            setSprite(AnimatedSprite *sprite, unsigned int imgWidth, unsigned int imgHeight) = 0;
    virtual double    getSpeed() = 0;
    // Speed en pixel/ms
    virtual void            setSpeed(double speed) = 0;
    virtual void            shoot() = 0;
    virtual void            move(const Direction &) = 0;
    virtual void            doSomeActions(int time) = 0;
    virtual Point<int> const     &getPosition() = 0;
    virtual void            die() = 0;
    virtual bool            isDead() = 0;
    virtual bool            spawn(const Point<int> &) = 0;
    virtual void            erase() = 0;
    virtual unsigned int    getSpriteWidth() = 0;
    virtual unsigned int    getSpriteHeight() = 0;
    virtual void            setPixelSize(unsigned int width, unsigned int height) = 0;
    virtual bool            setPosition(Point<int> const &) = 0;
    virtual ~IPlayer() {}
};

#endif // IPLAYER_H
