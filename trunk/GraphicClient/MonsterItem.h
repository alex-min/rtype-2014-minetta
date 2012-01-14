#ifndef MONSTERITEM_H
#define MONSTERITEM_H
#include "IPlayer.h"

class MonsterItem : public IPlayer
{
public:
    MonsterItem();
    void erase() {}
    void invalidateEvent() {}
};

#endif // MONSTERITEM_H
