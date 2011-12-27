#include "TinyMonster.h"

TinyMonster::TinyMonster() :
    APlayer(),_totalTime(0), _amplitude(0), _origine(0), _nbOscillation(0)
{
}

void            TinyMonster::shoot(void *fct)
{
    // TODO
    (void) fct;
}

bool TinyMonster::isOutOfScreen()
{
    return (_pos.getX() + _w < 0.0 || _pos.getY() < 0.0 || _pos.getY() > _screenHeight);
}

void            TinyMonster::update(UInt32 time)
{
    // TODO
    if (isOutOfScreen())
        return;
    _totalTime += time;
    _pos.setX(_speed * _totalTime);
    _pos.setY(_origine + (_amplitude * cos(_pos.getX() /
                                           (_screenWidth / (_nbOscillation * 2 * M_PI)))));
    _pos.setX(_screenWidth - _pos.getX());
    if (isOutOfScreen())
        return;
}

TinyMonster::~TinyMonster()
{

}

int TinyMonster::getAmplitude()
{
    return (_amplitude);
}

void TinyMonster::setAmplitude(UInt32 amplitude)
{
    _amplitude = amplitude;
}

int TinyMonster::getNbOscillation()
{
    return (_nbOscillation);
}

void TinyMonster::setNbOscillation(UInt32 nbOscillation)
{
    _nbOscillation = nbOscillation;
}
