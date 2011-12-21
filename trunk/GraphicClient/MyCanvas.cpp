#include "MyCanvas.h"

MyCanvas::MyCanvas(QWidget* parent, const QPoint& position, const QSize& size, UInt32 frameTime) :
    QSFMLCanvas(parent, position, size, frameTime)
{

}

void MyCanvas::onInit()
{
    _a = new AnimatedImage("r-typesheet21.png");

    _a->parseFile();
}

void MyCanvas::onUpdate()
{
    Clear(sf::Color(0, 0, 0));

    //    if (GameSingleton::getInstance()->getBackground())

    Int32 posX = 0;
    Int32 posY = 0;

    for (std::list<sf::Sprite*>::const_iterator it = _a->getSpriteList().begin(); it != _a->getSpriteList().end(); ++it)
    {
        (*it)->SetPosition(posX, posY);
        Draw(**it);

        if ((posX + 40) >= _size.width())
        {
            posX = 0;
            posY += 40;
        }
        else
            posX += 40;
    }
}
