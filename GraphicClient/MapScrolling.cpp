#include "MapScrolling.h"

MapScrolling::MapScrolling() :
    _speed(0.1),
    _map(NULL)
{
    _resizeX = 0;
    _resizeY = 0;
    _screenSize.setCoord(0,0);
    _starttime = 0;
    _elapsedTime = 0;
    _conf = ConfLoader::getInstance()->getConfObjectFor("../blockMapping.ini");
    _spriteIterator = _wallPool.getMapList().begin();
}

void            MapScrolling::setScreenWidth(UInt32 width)
{
    _screenSize.setX(width);
}

void            MapScrolling::setScreenHeight(UInt32 height)
{
    _screenSize.setY(height);
}

void            MapScrolling::computeSquareSize()
{
    _resizeX = static_cast<float> (_screenSize.getX()) / _map->getMap()[0].size();
    _resizeY = static_cast<float> (_screenSize.getY()) / _map->getMap()[0].size();
    _resizeY += 2;
    LOG <<_resizeX << std::endl;
}

void            MapScrolling::load(UInt8 id)
{
    LOGERR << "@@stub" << std::endl;
    (void) id;
    String mapId = "";
    mapId = String::toString(id - '0');

    _map = new MapLoader("../map_example" + mapId + ".ma");
    MapScrolling::computeSquareSize();
    for (UInt16 i = 0; i < _conf->getSize(); ++i)
    {
        String filename = _conf->getStringValueOf(_conf->at(i));
        AnimatedImage *a = new AnimatedImage(filename);
        a->getSprite().Resize(_resizeX, _resizeY);
        _imageMapping[i] = a;
    }

}

void            MapScrolling::setStartTime(UInt64 time)
{
    _starttime = time;
}

void            MapScrolling::update(UInt16 elapsedTime)
{
    if (_screenSize.getX() == 0 || _screenSize.getY() == 0)
        throw Exception("MapScrolling::update : " "screenSize cannot be null");
    if (!_map)
        throw Exception("MapScrolling::update : "  " map is not loaded");
    _spriteIterator = _wallPool.getMapList().begin();
    PoolFactory<Wall>::ListType & wallmap = _wallPool.getMapList();

    for (PoolFactory<Wall>::ListType::iterator it = wallmap.begin(); it != wallmap.end(); ++it) {
        if (it->second == false) {
            it->first->setX(it->first->getX()
                            - _speed * elapsedTime);
            if (it->first->getX() + _resizeX < 0)
                _wallPool.invalidate(it->first);
        }
    }

    MapLoader::tabInt &map = _map->getMap();
    //LOG << _elapsedTime * _speed << std::endl;
    static UInt64 cur2 = 0;
    Int64 cur = (_elapsedTime * _speed) / (_resizeX - 2);
    //LOG << "CUR" << map[0].size() << " " << cur << std::endl;
    // cur -= 5;
    if (cur < map.size() - 1 && cur2 != cur && cur >= 0) {
        for (unsigned int i = 0; i < map[0].size(); i++) {
            if (map[cur][i] != 0) {
                Wall *w = _wallPool.generate();
                w->setX(800);
                w->setY((map[0].size() - i - 1) * (_resizeY - 2));
                w->setSprite(_imageMapping[map[cur][i] - 1]);
                w->setW(_resizeX);
                w->setH(_resizeY);
            }
        }
    }
    cur2 = cur;
    _elapsedTime += elapsedTime;
}

Wall            *MapScrolling::getNextWall()
{
    if (_spriteIterator == _wallPool.getMapList().end() ||
            _wallPool.getMapList().size() == 0)
        return (NULL);
    while (_spriteIterator != _wallPool.getMapList().end()
           && _spriteIterator->second == true)
        ++_spriteIterator;
    if (_spriteIterator == _wallPool.getMapList().end())
        return (NULL);
    Wall    *w = _spriteIterator->first;
    ++_spriteIterator;
    return (w);
}
