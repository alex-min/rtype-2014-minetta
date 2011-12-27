#ifndef MISSILE_H
#define MISSILE_H

#include "Missile_global.h"
#include "APlayer.h"

class MISSILESHARED_EXPORT Missile : public APlayer{
public:
    Missile();
    virtual void            shoot(void *);
    void    update(UInt32 time);
    bool isOutOfScreen();
    virtual ~Missile();
private:
    void                    moveLeft(UInt32 time);
    void                    moveRight(UInt32 time);
    void                    moveUp(UInt32 time);
    void                    moveDown(UInt32 time);
    struct direction
    {
        IPlayer::e_Direction dir;
        void (Missile::*fct)(UInt32 time);
    };
    direction gl_tab[6];
    UInt32 _totalTime;
    PointF _origine;
    IPlayer::e_Direction _direct;

};

extern "C"
{
MISSILESHARED_EXPORT IPlayer *createAndFill(unsigned int screenWidth, unsigned int screenHeight,
                                            float x, float y)
{
    Missile *mis = new Missile();
    mis->setScreenSize(screenWidth, screenHeight);
    mis->setPosition(x,y);
    return (mis);
}
MISSILESHARED_EXPORT IPlayer *create()
{
    return (new Missile());
}
}

#endif // MISSILE_H
