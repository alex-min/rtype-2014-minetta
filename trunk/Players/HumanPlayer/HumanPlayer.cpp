#include "HumanPlayer.h"
#include "Missile.h"

HumanPlayer::s_movement HumanPlayer::_movementTab[] =
{
    {sf::Key::Left, &HumanPlayer::moveLeft},
    {sf::Key::Right,&HumanPlayer::moveRight},
    {sf::Key::Up,&HumanPlayer::moveUp},
    {sf::Key::Down,&HumanPlayer::moveDown},
    {(sf::Key::Code)(0), 0}
};

HumanPlayer::HumanPlayer() :
    APlayer(),
    _right(false),
    _up(false),
    _down(false),
    _outOfScreen(false)
{
    _keys.push_back(sf::Key::Left);
    _keys.push_back(sf::Key::Right);
    _keys.push_back(sf::Key::Up);
    _keys.push_back(sf::Key::Down);
    _keys.push_back(sf::Key::Space);

    _speed = 1.280;
    _isDead = false;
}

void    HumanPlayer::setSpeed(double speed)
{
    _speed = speed;
}

HumanPlayer::~HumanPlayer()
{

}

IPlayer            *HumanPlayer::shoot(void *fct)
{
    Player::MissilFunc addMissil = reinterpret_cast<Player::MissilFunc>(fct);
    Missile *missil = reinterpret_cast<Missile*>(addMissil());

    missil->setScreenSize(_screenWidth, _screenHeight);

    missil->setPosition(getPosition().getX() + _w + 5, getPosition().getY());
    missil->setDirection(1.0, 0.0);

    _shoot = false;

    return (missil);
}

bool            HumanPlayer::isOutOfScreen()
{
    return (_outOfScreen);
}

void            HumanPlayer::moveLeft(UInt32 time)
{
    if ((_pos.getX() - (time *_speed)) >= 0)
        _pos.setX(_pos.getX() - (time *_speed));
}

void            HumanPlayer::moveRight(UInt32 time)
{
    if (((_pos.getX() + _w) + (time *_speed)) <= _screenWidth)
        _pos.setX(_pos.getX() + (time *_speed));
}

void            HumanPlayer::moveUp(UInt32 time)
{
    if ((_pos.getY() - (time *_speed)) >= 0)
        _pos.setY(_pos.getY() - (time *_speed));
}

void            HumanPlayer::moveDown(UInt32 time)
{
    if (((_pos.getY() + _h) + (time *_speed)) <= _screenHeight)
        _pos.setY(_pos.getY() + (time *_speed));
}

void                    HumanPlayer::update(UInt32 time, EventReceiver &eventReceiver)
{
    for (std::list<sf::Key::Code>::iterator it = _keys.begin(); it != _keys.end(); ++it)
        if (eventReceiver.isKeyPressed(*it))
            for (int i = 0; _movementTab[i].fct; i++)
                if (_movementTab[i].keycode == *it)
                    (this->*(_movementTab[i].fct))(time);

    if (eventReceiver.isKeyPressed(sf::Key::Space))
        _shoot = true;

}

void            HumanPlayer::update(UInt32 time)
{
    (void)time;
}
