#include "ServerGame.h"
#include "ITime.h"

ServerGame::ServerGame() :
    _name("_DEFAULT_GAME_NAME")
{
}

void    ServerGame::setName(String const & name)
{
    _name = name;
}

void    ServerGame::generateGameName()
{
    _name = "_DEFAULT_GAME_NAME";
    MyTime t;
    t.setToMsTimeOfDay();
    _name += String(t.getMs());
}


void    ServerGame::run()
{
    while (1) {
        LOG << "running" << std::endl;
        MySleepMs(300);
    }
}


void    ServerGame::erase()
{
    // TODO : restart thread and start everything
}

void    ServerGame::invalidateEvent()
{
    // TODO : kill evrything and pause thread
}

