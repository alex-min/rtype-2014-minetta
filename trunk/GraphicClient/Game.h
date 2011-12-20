#ifndef GAME_H
#define GAME_H

#include "Common/Singleton.h"
#include "Image.h"
#include <list>

class Game
{
public:
    Game();
    bool        loadBackground(std::string const &filename);
    Image const *getBackground() const;
    Image       *getBackground();
    ~Game();
private:

    Image *_background;

    //    std::list<Player>    _players;
    //    std::list<Monster>  _monsters;

};

typedef Singleton<Game> GameSingleton;

#endif // GAME_H
