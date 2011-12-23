#ifndef GAME_H
#define GAME_H

#include <list>
#include "Singleton.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "APlayer.h"
#include "HumanPlayer.h"
#include "ITime.h"

class MyCanvas;

class Game
{
public:
    Game();
    bool        loadBackground(std::string const &filename);
    Image const *getBackground() const;
    Image       *getBackground();
    void        eventLoop(MyCanvas &app);
    ~Game();
private:

    EventReceiver   _eventReceiver;
    Image *_background;
    HumanPlayer     *_humanPlayer;
    MyTime _old_time;
     MyTime _cur_time;
    //    std::list<Player>    _players;
    //    std::list<Monster>  _monsters;

};

typedef Singleton<Game> GameSingleton;

#endif // GAME_H
