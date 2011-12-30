#include "MyCanvas.h"
#include "ListenServer.h"

MyCanvas::MyCanvas(QWidget* parent, const QPoint& position, const QSize& size, UInt32 frameTime) :
    QSFMLCanvas(parent, position, size, frameTime)
{
    connect(ListenServerSingleton::getInstance(), SIGNAL(posChanged()), GameSingleton::getInstance(), SLOT(updatePlayerPos()));
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
