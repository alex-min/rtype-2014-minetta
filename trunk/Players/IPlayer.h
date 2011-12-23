#ifndef IPLAYER_H
#define IPLAYER_H

#include "Point.h"
#include "SystemDefines.h"
#include "Object.h"

class IPlayer : public Object<float>
{
public:
    enum e_Direction{
        LEFT,
        RIGHT,
        UP,
        DOWN,
        UNKNOWN
    };
    virtual void            *getSprite() = 0;
    virtual void            setSprite(void *sprite, float imgWidth, float imgHeight) = 0;
    virtual double          getSpeed() = 0;
    virtual void            setSpeed(double speed) = 0;
    virtual void            shoot(void *) = 0;
    virtual void            die() = 0;
    virtual bool            isDead() = 0;
    virtual void            spawn(Point<float> const &) = 0;
    virtual void            erase() = 0;
    virtual float           getSpriteWidth() = 0;
    virtual float           getSpriteHeight() = 0;
    virtual void            setSize(float width, float height) = 0;
    virtual ~IPlayer() {}
};

#endif // IPLAYER_H
