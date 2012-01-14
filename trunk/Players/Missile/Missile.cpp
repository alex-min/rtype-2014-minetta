#include "Missile.h"

Missile::Missile() :
    APlayer(), _direct(0.0,0.0)
{
}

void Missile::erase()
{
    APlayer::erase();
    _totalTime = 0;
    _direct.setX(0.0);
    _direct.setY(0.0);
}

void                    Missile::setDirection(float a, float b)
{
    _direct.setX(a);
    _direct.setY(b);
}

void                    Missile::setDirection(PointF vect)
{
    _direct.setX(vect.getX());
    _direct.setY(vect.getY());
}

IPlayer            *Missile::shoot(void *fct)
{
    (void) fct;

    return (0);
}

void            Missile::update(UInt32 time)
{
    _totalTime += time;
    setPosition(_pos.getX() + _direct.getX() * time,
                _pos.getY() + _direct.getY() * time);
}

Missile::~Missile()
{

}

bool Missile::isOutOfScreen()
{
    return (_pos.getX() > _screenWidth || _pos.getX() + _w < 0.0 ||
            _pos.getY() + _h < 0.0 || _pos.getY() > _screenWidth);
}

extern "C"
{
MISSILESHARED_EXPORT IPlayer *createAndFill(UInt32 screenWidth, UInt32 screenHeight,
                                            float x, float y, float a, float b)
{
    Missile *mis = new Missile();
    mis->setScreenSize(screenWidth, screenHeight);
    mis->setPosition(x,y);
    mis->setDirection(a,b);
    return (mis);
}
MISSILESHARED_EXPORT IPlayer *create()
{
    return (new Missile());
}
}
