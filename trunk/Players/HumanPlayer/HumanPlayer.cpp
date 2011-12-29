#include "HumanPlayer.h"

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
    _speed = 1.280;
}

void    HumanPlayer::setSpeed(double speed)
{
    _speed = speed;
}

HumanPlayer::~HumanPlayer()
{

}

void            HumanPlayer::shoot(void *)
{
    //TODO
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
}
