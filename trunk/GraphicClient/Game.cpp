#include <QApplication>
#include "Game.h"
#include "MyCanvas.h"
#include "ITime.h"

Game::Game()
{
    _background = 0;

    AnimatedImage *a = new AnimatedImage("r-typesheet42.png");

    a->parseFile();

    _humanPlayer = new HumanPlayer();
    _humanPlayer->setSprite(a, a->getCurrentSprite()->GetSize().x, a->getCurrentSprite()->GetSize().y);

    _old_time.setToMsTimeOfDay();
}

void        Game::updateScreenSize()
{
   _humanPlayer->setScreenSize(_screenSize.width(), _screenSize.height());
}

void        Game::updateSprites(sf::Sprite *playerSprite)
{
    Point<float> p = _humanPlayer->getPosition();

    playerSprite->SetPosition(_humanPlayer->getX(), _humanPlayer->getY());
}

void        Game::eventLoop(MyCanvas &app)
{
    sf::Event event;

    while (app.GetEvent(event))
        _eventReceiver.OnEvent(event);

    if (_eventReceiver.isKeyPressed(sf::Key::Escape))
    {
        std::cout << "Window Closed." << std::endl;
        qApp->quit();
    }

    _cur_time.setToMsTimeOfDay();
    _humanPlayer->update(_cur_time.getMs() - _old_time.getMs(), _eventReceiver);
    _old_time.setToMsTimeOfDay();

    sf::Sprite *sprite = reinterpret_cast<AnimatedImage *>(_humanPlayer->getSprite())->getCurrentSprite();

    updateSprites(sprite);

    app.Draw(*sprite);
}

void        Game::setScreenSize(QSize const &screenSize)
{
    _screenSize = screenSize;
    _humanPlayer->setScreenSize(screenSize.width(), screenSize.height());
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

void    Game::updatePlayerPos()
{

}

Game::~Game()
{
    if (_background)
        delete _background;
}
