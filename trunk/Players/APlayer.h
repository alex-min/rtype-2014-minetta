#ifndef APLAYER_H
#define APLAYER_H

#include "IPlayer.h"

class APlayer : public IPlayer
{
public:
    APlayer(double speed = 1.280);
    virtual const AnimatedSprite          *getSprite();
    virtual void                setSprite(AnimatedSprite *sprite, unsigned int imgWidth, unsigned int imgHeight);
    virtual double              getSpeed();
    // Speed en pixel/ms
    virtual void                setSpeed(double speed);
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
    double             _speed;
    Point<int>                  _position;
    AnimatedSprite              *_sprite;
    bool                        _isDead;
    unsigned int                _widthSize;
    unsigned int                _heightSize;
};

#endif // APLAYER_H
