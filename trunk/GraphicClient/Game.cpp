#include <QApplication>
#include "Game.h"
#include "MyCanvas.h"

Game::Game()
{
    _background = 0;
}

void        Game::eventLoop(MyCanvas &app, sf::Clock &clock)
{
    sf::Event Event;

    while (app.GetEvent(Event))
    {
        if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
        {
            std::cout << "Window Closed !" << std::endl;
            qApp->quit();
        }
    }

    // Get elapsed time since last frame (we could as well use App.GetFrameTime())
    float ElapsedTime = clock.GetElapsedTime();
    clock.Reset();

    //           if (App.GetInput().IsKeyDown(sf::Key::Left))  Left -= Speed * ElapsedTime;
    //           if (App.GetInput().IsKeyDown(sf::Key::Right)) Left += Speed * ElapsedTime;
    //           if (App.GetInput().IsKeyDown(sf::Key::Up))    Top  -= Speed * ElapsedTime;
    //           if (App.GetInput().IsKeyDown(sf::Key::Down))  Top  += Speed * ElapsedTime;
}

bool        Game::loadBackground(std::string const &filename)
{
    if (_background)
        delete _background;

    _background = new Image(filename);

    if (_background->hasImageLoaded())
        return (true);

    return (false);
}

Image const *Game::getBackground() const
{
    return (_background);
}

Image       *Game::getBackground()
{
    return (_background);
}

Game::~Game()
{
    if (_background)
        delete _background;
}
