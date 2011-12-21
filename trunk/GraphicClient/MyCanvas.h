#ifndef MYCANVAS_H
#define MYCANVAS_H

#include "QSFMLCanvas.h"
#include <Qt/qframe.h>
#include "Game.h"
#include "AnimatedImage.h"

class MyCanvas : public QSFMLCanvas
{
public :

    MyCanvas(QWidget* parent, const QPoint& position, const QSize& size, UInt32 frameTime = 0);

private :

    virtual void onInit();
    virtual void onUpdate();

private:
AnimatedImage   *_a;

};

#endif // MYCANVAS_H
