#include "Missile.h"

Missile::Missile(unsigned int screenWidth, unsigned int screenHeight,
                         unsigned int amplitude, unsigned int origine, unsigned int nbOscillation) :
    APlayer(), _screenWidth(screenWidth), _screenHeight(screenHeight),
    _totalTime(0), _amplitude(amplitude / 2), _origine(origine), _nbOscillation(nbOscillation)
{
    if (_origine > _screenHeight)
        throw new Exception("Invalid Monster params");
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

void            Missile::shoot()
{
    // TODO
}

void            Missile::moveUp()
{
    _position.setY(_screenHeight - (_speed * _totalTime));
}

void            Missile::moveDown()
{
    _position.setY(_speed * _totalTime);
}

void            Missile::moveLeft()
{
    _position.setX(_screenWidth - (_speed * _totalTime));
}

void            Missile::moveRight()
{
    _position.setX(_speed * _totalTime);
}

void            Missile::move(const Direction &dir)
{
    int val = 0;

    while (gl_tab[val].fct)
    {
        if (gl_tab[val].dir == dir)
        {
            (this->*(gl_tab[val].fct))();
            return ;
        }
        val++;
    }
}

void            Missile::doSomeActions(int time)
{
    _totalTime += time;
    move(IPlayer::LEFT);
}

Missile::~Missile()
{

}
