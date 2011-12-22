#ifndef GAME_H
#define GAME_H

#include <list>
#include "Singleton.h"
#include "AnimatedImage.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "APlayer.h"

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

    EventReceiver   _eventReceiver;
    Image *_background;
    AnimatedImage   *_a;

    //    std::list<Player>    _players;
    //    std::list<Monster>  _monsters;

};

typedef Singleton<Game> GameSingleton;

#endif // GAME_H
