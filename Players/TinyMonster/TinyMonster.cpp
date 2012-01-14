#include "Missile.h"
#include "TinyMonster.h"

TinyMonster::TinyMonster() :
    APlayer(),_totalTime(0), _lastShootTime(0), _amplitude(200), _nbOscillation(1), _wantToShoot(false)
{
}

IPlayer            *TinyMonster::shoot(void *fct)
{
    Player::missileFactory getMissile = reinterpret_cast<Player::missileFactory>(fct);
    Missile *missile = reinterpret_cast<Missile*>(getMissile());

    missile->setScreenSize(_screenWidth, _screenHeight);
    missile->setDirection(-0.4, 0);
    missile->setPosition(getPosition().getX() - 5, getPosition().getY() + 5);

    _shoot = false;

    return (missile);
}

bool TinyMonster::isOutOfScreen()
{
//    return (_pos.getX() + _w < 0.0 || _pos.getY() < 0.0 || _pos.getY() > _screenHeight);
    return (false);
}

void            TinyMonster::update(UInt32 time)
{
    _totalTime += time;
//    _shootTime += time;

//    if (_shootTime >= 200)
//    {
//        _shoot = true;
//        _shootTime = 0;
//    }

    _pos.setX(_speed * _totalTime);
    _pos.setY(_origin.getY() + (_amplitude * cos(_pos.getX() /
                                                 (_screenWidth / (_nbOscillation * 2 * M_PI)))));
    _pos.setX(_screenWidth - _pos.getX());

    if (_totalTime - _lastShootTime >= 2000)
    {
        _lastShootTime = _totalTime;
        _shoot = true;
    }
}

void TinyMonster::setPosition(float x, float y)
{
    if (_origin.getY() == -1)
        _origin.setY(y);
    _oldPos = _pos;
    _pos.setCoord(x, y);
}

void            TinyMonster::erase()
{
    APlayer::erase();
    _origin.setY(-1);
    _lastShootTime = 0;
    _totalTime = 0;
//    _shootTime = 0;
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

extern "C"
{
TINYMONSTERSHARED_EXPORT IPlayer *createAndFill(UInt32 screenWidth, UInt32 screenHeight,
                                                UInt32 amplitude, UInt32 origine, UInt32 nbOscillation)
{
    TinyMonster *monster = new TinyMonster();
    monster->setScreenSize(screenWidth, screenHeight);
    monster->setAmplitude(amplitude);
    monster->setPosition(screenWidth, origine);
    monster->setOrigin(PointF(0, origine));
    monster->setNbOscillation(nbOscillation);
    return (monster);
}
TINYMONSTERSHARED_EXPORT IPlayer *create()
{
    return (new TinyMonster());
}
}
