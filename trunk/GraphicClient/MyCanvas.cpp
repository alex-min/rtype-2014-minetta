#include "MyCanvas.h"

MyCanvas::MyCanvas(QWidget* parent, const QPoint& position, const QSize& size, UInt32 frameTime) :
    QSFMLCanvas(parent, position, size, frameTime)
{
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
}
