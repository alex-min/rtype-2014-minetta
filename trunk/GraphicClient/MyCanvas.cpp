#include "MyCanvas.h"

MyCanvas::MyCanvas(QWidget* parent, const QPoint& position, const QSize& size, unsigned int frameTime) :
    QSFMLCanvas(parent, position, size, frameTime)
{

}

void MyCanvas::onInit()
{
    _a = new AnimatedImage("r-typesheet10.png");

    _a->parseFile();
    std::cout << "nombre d'elements: " << _a->getMonsters().size() << std::endl;
}

void MyCanvas::onUpdate()
{
    Clear(sf::Color(0, 128, 0));

    //    if (GameSingleton::getInstance()->getBackground())

    int posX = 0;
    int posY = 0;

    for (std::list<sf::Sprite*>::const_iterator it = _a->getMonsters().begin(); it != _a->getMonsters().end(); ++it)
    {
        if (posX > _size.width())
        {
            posX = 0;
            posY += 50;
        }
        if (posY > _size.height())
            break;

        posX += 50;

        (*it)->SetPosition(posX, posY);
        Draw(**it);
    }
}
