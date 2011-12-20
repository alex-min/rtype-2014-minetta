#ifndef MYCANVAS_H
#define MYCANVAS_H

#include "QSFMLCanvas.h"
#include <Qt/qframe.h>
#include "Game.h"

class MyCanvas : public QSFMLCanvas
{
public :

    MyCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size, unsigned int frameTime = 0);

private :

    virtual void onInit();
    virtual void onUpdate();

private:

};

#endif // MYCANVAS_H
