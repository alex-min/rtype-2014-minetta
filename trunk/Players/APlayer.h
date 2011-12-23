#ifndef APLAYER_H
#define APLAYER_H

#include "IPlayer.h"
#include "SystemDefines.h"

class APlayer : public IPlayer
{
public:
    APlayer(double speed = 0.0, void *sprite = 0, bool isDead = true);
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
    virtual void                setScreenSize(float screenWidth, float screenHeight);
    virtual ~APlayer();

protected:
    double                      _speed;
    void                        *_sprite;
    bool                        _isDead;
    float                       _screenWidth;
    float                       _screenHeight;
};

#endif // APLAYER_H
