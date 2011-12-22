#include <QApplication>
#include "Game.h"
#include "MyCanvas.h"

Game::Game()
{
    _background = 0;

    AnimatedImage *a = new AnimatedImage("r-typesheet42.png");

    a->parseFile();

    _humanPlayer = new HumanPlayer();
    _humanPlayer->setSprite(a, 10, 10);
}

//void        Game::updateSprites()
//{
//    Point<float> p = _humanPlayer->getPosition()
//}

void        Game::eventLoop(MyCanvas &app, GameClock &clock)
{
    static sf::Clock cl;

    std::cout << "sfml -> elapsedTime: " << cl.GetElapsedTime() << std::endl;
    cl.Reset();

    sf::Event event;

    while (app.GetEvent(event))
        _eventReceiver.OnEvent(event);

    if (_eventReceiver.isKeyPressed(sf::Key::Escape))
    {
        std::cout << "Window Closed." << std::endl;
        qApp->quit();
    }

    UInt32 elapsedTime = clock.getOldTime() - clock.getCurrentTime();

    std::cout << "GameClock: elapsedTime: " << elapsedTime << std::endl;

    clock.setOldTime(clock.getCurrentTime());

    _humanPlayer->update(elapsedTime, _eventReceiver);

//    updateSprites();

    AnimatedImage *animatedImage = reinterpret_cast<AnimatedImage *>(_humanPlayer->getSprite());

    sf::Sprite *sprite = animatedImage->getSpriteList().front();
    sprite->SetPosition(_humanPlayer->getPosition().getX(), _humanPlayer->getPosition().getY());

    app.Draw(*sprite);
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
