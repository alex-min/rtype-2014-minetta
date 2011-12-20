#include "MyCanvas.h"

MyCanvas::MyCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size, unsigned int frameTime) :
    QSFMLCanvas(Parent, Position, Size, frameTime)
{

}

void MyCanvas::onInit()
{

}

void MyCanvas::onUpdate()
{
    Clear(sf::Color(0, 128, 0));

//    _image.getSprite().Rotate(GetFrameTime() * 100.f);

    if (GameSingleton::getInstance()->getBackground())
    Draw(GameSingleton::getInstance()->getBackground()->getSprite());
}
