#ifndef GAME_H
#define GAME_H

#include "Singleton.h"
#include "Image.h"
#include "SFML/Graphics.hpp"
#include <list>

class MyCanvas;

class Game
{
public:
    Game();
    bool        loadBackground(std::string const &filename);
    Image const *getBackground() const;
    Image       *getBackground();
    void        eventLoop(MyCanvas &app, sf::Clock &clock);
    ~Game();
private:

    Image *_background;

    //    std::list<Player>    _players;
    //    std::list<Monster>  _monsters;

};

typedef Singleton<Game> GameSingleton;

#endif // GAME_H
