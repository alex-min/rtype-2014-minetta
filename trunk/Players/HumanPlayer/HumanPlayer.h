#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include <list>
#include "APlayer.h"
#include "EventReceiver.h"
#include "Timer.h"
#include "AnimatedImage.h"

class HumanPlayer : public APlayer
{
public:
    struct s_movement
    {
        sf::Key::Code   keycode;
        void    (HumanPlayer::*fct)(UInt32 time);
    };

    HumanPlayer();
    virtual void            shoot(void *);
    void                    moveLeft(UInt32 time);
    void                    moveRight(UInt32 time);
    void                    moveUp(UInt32 time);
    void                    moveDown(UInt32 time);
    void                    update(UInt32 time, EventReceiver &eventReceiver);
    virtual void            setSpeed(double speed);
    virtual                 ~HumanPlayer();

protected:
    Timer   _timer;
    bool    _right;
    bool    _up;
    bool    _down;

private:
    static s_movement          _movementTab[5];
    std::list<sf::Key::Code>   _keys;
};

#endif // HUMANPLAYER_H