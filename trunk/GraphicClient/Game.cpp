#include <QApplication>
#include "Game.h"
#include "MyCanvas.h"

Game::Game()
{
    _background = 0;

    _a = new AnimatedImage("r-typesheet42.png");

    _a->parseFile();
}

void        Game::eventLoop(MyCanvas &app, sf::Clock &clock)
{
    sf::Event event;

    while (app.GetEvent(event))
        _eventReceiver.OnEvent(event);

    if (_eventReceiver.isKeyPressed(sf::Key::Escape))
    {
        std::cout << "Window Closed." << std::endl;
        qApp->quit();
    }

    if (_eventReceiver.isKeyPressed(sf::Key::Right))
    {
        sf::Sprite *sprite = _a->getSpriteList().front();

        float ElapsedTime = clock.GetElapsedTime();

        sprite->SetPosition(sprite->GetPosition().x + ElapsedTime * 500, sprite->GetPosition().y);
    }

    clock.Reset();

    app.Draw(*(_a->getSpriteList().front()));
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
