#ifndef APLAYER_H
#define APLAYER_H

#include "IPlayer.h"

class APlayer : public IPlayer
{
public:
    APlayer(double speed = 1.280, void *sprite = 0, bool isDead = true);
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
    virtual ~APlayer();

protected:
    double                      _speed;
    void                        *_sprite;
    bool                        _isDead;
};

#endif // APLAYER_H
