#ifndef APLAYER_H
#define APLAYER_H

#include "IPlayer.h"
#include "SystemDefines.h"

class APlayer : public IPlayer
{
public:
    APlayer();
    virtual void *              getSprite();
    virtual void                setSprite(void *sprite, float imgWidth, float imgHeight);
    virtual double              getSpeed();
    virtual void                setSpeed(double speed);
    virtual void                die();
    virtual bool                isDead();
    virtual void                spawn(const Point<float> &);
    virtual float               getSpriteWidth();
    virtual void                erase();
    virtual float               getSpriteHeight();
    virtual void                setSize(float width, float height);
    virtual void                setScreenSize(UInt32 screenWidth, UInt32 screenHeight);
    virtual void                setOrigin(Point<float> const &origin);
    virtual ~APlayer();

protected:
    double                      _speed;
    void                        *_sprite;
    bool                        _isDead;
    UInt32                      _screenWidth;
    UInt32                      _screenHeight;
    Point<float>                _origin;
};

#endif // APLAYER_H
