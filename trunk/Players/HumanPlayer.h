#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "APlayer.h"

class HumanPlayer : public APlayer
{
public:
    HumanPlayer();
    virtual void            shoot();
    virtual void            move(const Direction &);
    virtual void            doSomeActions(int time);
    virtual ~HumanPlayer();
protected:
    bool _left;
    bool _right;
    bool _up;
    bool _down;
};

#endif // HUMANPLAYER_H
