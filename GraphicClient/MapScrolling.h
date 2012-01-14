#ifndef MAPSCROLLING_H
#define MAPSCROLLING_H
#include <map>
#include "MapLoader.h"
#include "MapScrolling.h"
#include "Pool.h"
#include "ConfLoader.hpp"
#include "Object.h"
#include "MyString.h"
#include "Wall.h"
#include "AnimatedImage.h"

class MapScrolling
{
public:
    MapScrolling();
    void            load(UInt8 id);
    void            update(UInt16 elapsedTime);

    void            setSpeed(UInt16 speed)      { _speed = speed; }
    UInt16          getSpeed() const            { return (_speed); }
    Wall            *getNextWall();
    void            setStartTime(UInt64 time);
    void            setScreenWidth(UInt32 width);
    void            setScreenHeight(UInt32 height);

private:
    void            computeSquareSize();

private:
    UInt64                                  _starttime;
    std::map<int,AnimatedImage *>           _imageMapping;
    float                                  _speed;
    MapLoader                               *_map;
    PoolFactory < Wall >                    _wallPool;
    ConfObject                              const*_conf;
    UInt64                                   _elapsedTime;
    PoolFactory<Wall>::ListType::iterator   _spriteIterator;
    Point < UInt32  >                       _screenSize;
    float                                   _resizeX;
    float                                   _resizeY;
};

#endif // MAPSCROLLING_H
