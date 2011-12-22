#include "TinyMonster.h"

TinyMonster::TinyMonster(unsigned int screenWidth, unsigned int screenHeight,
                         unsigned int amplitude, unsigned int origine, unsigned int nbOscillation) :
    APlayer(), _screenWidth(screenWidth), _screenHeight(screenHeight),
    _totalTime(0), _amplitude(amplitude / 2), _origine(origine), _nbOscillation(nbOscillation)
{
    if ((_origine + _amplitude) > _screenHeight || (_origine - _amplitude) < 0)
        throw new Exception("Invalid Monster params");
}

void            TinyMonster::shoot()
{
    // TODO
}

void            TinyMonster::update(UInt32 time)
{
       _totalTime += time;
       _pos.setX(_speed * _totalTime);
       _pos.setY(_origine + (_amplitude * cos(_pos.getX() /
                                                   (_screenWidth / (_nbOscillation * 2 * M_PI)))));
       _pos.setX(_screenWidth - _pos.getX());
}

TinyMonster::~TinyMonster()
{

}

