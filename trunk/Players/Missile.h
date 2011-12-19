#ifndef MISSILE_H
#define MISSILE_H

#include "Common/Exception.h"
#include "APlayer.h"

class Missile : public APlayer
{
public:
    Missile(unsigned int screenWidth, unsigned int screenHeight, unsigned int amplitude,
               unsigned int origine, unsigned int nbOscillation = 10);
    virtual void            shoot();
    virtual void            move(const Direction &);
    virtual void            doSomeActions(int time);
    virtual ~Missile();
private:
    unsigned int _screenWidth;
    unsigned int _screenHeight;
    unsigned int _totalTime;
    unsigned int _amplitude;
    unsigned int _origine;
    unsigned int _nbOscillation;
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    struct direction
    {
        IPlayer::Direction dir;
        void (Missile::*fct)();
    };
    direction gl_tab[6];
};

#endif // MISSILE_H
