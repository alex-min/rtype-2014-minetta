#include "Missile.h"

Missile::Missile() :
    APlayer(), _direct(IPlayer::UNKNOWN)
{
    gl_tab[0].fct = &Missile::moveLeft;
    gl_tab[0].dir = IPlayer::LEFT;
    gl_tab[1].fct = &Missile::moveRight;
    gl_tab[1].dir = IPlayer::RIGHT;
    gl_tab[2].fct = &Missile::moveDown;
    gl_tab[2].dir = IPlayer::DOWN;
    gl_tab[3].fct = &Missile::moveUp;
    gl_tab[3].dir = IPlayer::UP;
    gl_tab[4].fct = 0;
    gl_tab[4].dir = IPlayer::UNKNOWN;
}

void            Missile::shoot(void *fct)
{
    (void) fct;
}

void            Missile::update(UInt32 time)
{
    _totalTime += time;
    int x = 0;
    while (gl_tab[x].fct != 0)
    {
        if (gl_tab[x].dir == _direct)
            return (this->*(gl_tab[x].fct))(time);
    }
}

Missile::~Missile()
{

}

void            Missile::moveLeft(UInt32 time)
{
    _pos.setX(_pos.getX() - (time *_speed));
}

void            Missile::moveRight(UInt32 time)
{
    _pos.setX(_pos.getX() + (time *_speed));
}

void            Missile::moveUp(UInt32 time)
{
    _pos.setY(_pos.getY() - (time *_speed));
}

void            Missile::moveDown(UInt32 time)
{
    _pos.setY(_pos.getY() + (time *_speed));
}

bool Missile::isOutOfScreen()
{
    return (_pos.getX() > _screenWidth || _pos.getX() + _w < 0.0 ||
            _pos.getY() + _h < 0.0 || _pos.getY() > _screenWidth);
}
