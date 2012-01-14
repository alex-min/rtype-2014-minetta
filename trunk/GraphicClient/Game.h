#ifndef GAME_H
#define GAME_H

#include <map>
#include <QSize>
#include <QObject>
#include "Singleton.h"
#include "Sfml.h"
#include "APlayer.h"
#include "HumanPlayer.h"
#include "ITime.h"
#include "Scrolling.h"
#include "MapLoader.h"
#include "MapScrolling.h"
#include "TinyMonster.h"
#include "Missile.h"
#include "MonsterItem.h"
#include "Sounds.h"
#include <list>

class MyCanvas;

namespace Player
{
typedef IPlayer* (*FuncType)(UInt32,UInt32,UInt32,UInt32,UInt32);
}

class Game : public QObject
{
    Q_OBJECT

public:
    Game();
    bool        loadBackground(std::string const &filename);
    Image const *getBackground() const;
    Image       *getBackground();
    void        eventLoop(MyCanvas &app);
    void        updateSprites(MyCanvas &app);
    void        setScreenSize(QSize const &screenSize);
    void        updateScreenSize();
    void        updateAnimatedSprites(MyCanvas &app);
    void        drawWaitingSprite(MyCanvas &app);
    void        setStartGame(bool b);
    void        setMapId(UInt8 mapId);
    ~Game();

public slots:
    void    updatePlayerPos(UInt16 id, UInt16 x, UInt16 y);
    void    pop(UInt16 id,UInt8 monsterType, UInt16 x, UInt16 y, Int32);
    void    playerDie(UInt16 id);

private:

    EventReceiver       _eventReceiver;
    Image               *_background;
    HumanPlayer         *_humanPlayer;
    MyTime              _old_time;
    MyTime              _old_time_pos;
    MyTime              _cur_time;
    QSize               _screenSize;
    std::map<UInt16, IPlayer*> _players;
    std::map<UInt16, IPlayer*> _missils;
    std::map<UInt16, IPlayer*> _monsterMissils;
    TinyMonster             *_monster;
    Scrolling            _scroll;
    MapLoader            *_map;
    MapScrolling         _mapScroll;
    AnimatedImage        *_explosion;
    PoolFactory < IPlayer > _monsterPool;
    bool                    _started;
    Sounds                  *_soundsManager;
    UInt8                   _mapId;
};

std::map<UInt16, IPlayer *> *            backupMissil(bool save, std::map<UInt16, IPlayer *> *ptr);
IPlayer*        addMissil();
std::map<UInt16, IPlayer *> *            backupMonsterMissil(bool save, std::map<UInt16, IPlayer *> *ptr);
IPlayer*        addMonsterMissil();

typedef Singleton<Game> GameSingleton;

#endif // GAME_H
