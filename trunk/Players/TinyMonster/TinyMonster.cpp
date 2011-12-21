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

void            TinyMonster::move(const Direction &dir)
{
    (void) dir;
    _position.setX(_speed * _totalTime);
    _position.setY(_origine + (_amplitude * cos(_position.getX() /
                                                (_screenWidth / (_nbOscillation * 2 * M_PI)))));
    _position.setX(_screenWidth - _position.getX());
}

void            TinyMonster::doSomeActions(int time)
{
    _totalTime += time;
    move(IPlayer::LEFT);
}

TinyMonster::~TinyMonster()
{

}
