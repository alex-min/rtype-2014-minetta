#include "MyCanvas.h"

MyCanvas::MyCanvas(QWidget* parent, const QPoint& position, const QSize& size, UInt32 frameTime) :
    QSFMLCanvas(parent, position, size, frameTime)
{
    _waitingSprite = false;
}

void   MyCanvas::setWaitingSprite(bool b)
{
    _waitingSprite = b;
    GameSingleton::getInstance()->setStartGame(b);
}

void MyCanvas::onInit()
{
    GameSingleton::getInstance()->setScreenSize(_size);
}

void MyCanvas::onUpdate()
{
    Clear(sf::Color(0, 0, 0));

    //    if (GameSingleton::getInstance()->getBackground())

    GameSingleton::getInstance()->eventLoop(*this);
    if (_waitingSprite)
        GameSingleton::getInstance()->drawWaitingSprite(*this);
}
