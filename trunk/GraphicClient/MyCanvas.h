#ifndef MYCANVAS_H
#define MYCANVAS_H

#include "QSFMLCanvas.h"
#include <Qt/qframe.h>
#include "Game.h"
#include "AnimatedImage.h"
#include "Singleton.h"

class MyCanvas : public QSFMLCanvas
{
public :

    MyCanvas(QWidget* parent, const QPoint& position, const QSize& size, UInt32 frameTime = 0);
    void    setWaitingSprite(bool b);

private :

    virtual void onInit();
    virtual void onUpdate();

private:
    bool        _waitingSprite;
};

#endif // MYCANVAS_H
