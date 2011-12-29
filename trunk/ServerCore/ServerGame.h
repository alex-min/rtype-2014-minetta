#ifndef SERVERGAME_H
#define SERVERGAME_H
#include "Thread.h"
#include "MyString.h"
#include "MySleep.h"

class ServerGame : public Thread
{
public:
    ServerGame();
    void    setName(String const &);
    void    getName();
    void    generateGameName();
    virtual void run();
//pool methods
    void    erase();
    void    invalidateEvent();

protected:
    String  _name;
};

#endif // SERVERGAME_H
