#ifndef APLAYER_H
#define APLAYER_H

#include "IPlayer.h"
#include "SystemDefines.h"

class APlayer : public IPlayer
{
public:
    APlayer();
    virtual void                resetSprites();
    virtual void                setExplosionSprite(void *sprite, float imgWidth, float imgHeight);
    virtual void                switchToExplosionSprite();
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
    virtual UInt32              getScreenWidth() const;
    virtual UInt32              getScreenHeight() const;
    virtual void                setOrigin(Point<float> const &origin);
    virtual bool                getShoot() const;
    virtual void                setAvailibility(bool available);
    virtual bool                isAvailable() const;
    virtual ~APlayer();

protected:
    void                        *_backSprite;
    bool                        _available;
    float                       _expW;
    float                       _expH;
    float                       _expWB;
    float                       _expHB;
    double                      _speed;
    void                        *_sprite;
    void                        *_explosionSprite;
    bool                        _isDead;
    UInt32                      _screenWidth;
    UInt32                      _screenHeight;
    Point<float>                _origin;
    bool                        _shoot;
};

#endif // APLAYER_H
