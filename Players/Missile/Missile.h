#ifndef MISSILE_H
#define MISSILE_H

#include "Missile_global.h"
#include "APlayer.h"

class MISSILESHARED_EXPORT Missile : public APlayer{
public:
    Missile();
    virtual IPlayer            *shoot(void *);
    virtual void    update(UInt32 time);
    virtual bool isOutOfScreen();
    virtual void erase();

    void                    setDirection(float a, float b);
    void                    setDirection(PointF vect);
    virtual ~Missile();
private:

    UInt32 _totalTime;
    PointF _origine;
    PointF _direct;
};

#endif // MISSILE_H
