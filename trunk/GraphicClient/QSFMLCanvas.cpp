#include "QSFMLCanvas.h"

#ifdef Q_WS_X11
#include <Qt/qx11info_x11.h>
#include <X11/Xlib.h>
#endif

QSFMLCanvas::QSFMLCanvas(QWidget* parent, const QPoint& position, const QSize& size, UInt32 frameTime) :
    QWidget       (parent),
    _initialized (false)
{
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    setFocusPolicy(Qt::StrongFocus);

    move(position);
    resize(size);

    _pos = position;
    _size = size;
    _frameTime = frameTime;
    _timer.setInterval(frameTime);
}

QSFMLCanvas::~QSFMLCanvas()
{

}

bool    QSFMLCanvas::isInitialized()
{
    return (_initialized);
}

QSize const &QSFMLCanvas::getScreenSize()
{
    return (_size);
}

QPoint const &QSFMLCanvas::getPos()
{
    return (_pos);
}

UInt32 QSFMLCanvas::getFrameTime() const
{
    return (_frameTime);
}

void    QSFMLCanvas::setInitialized(bool init)
{
    _initialized = init;
}

void    QSFMLCanvas::setScreenSize(QSize const &size)
{
    _size = size;
}

void    QSFMLCanvas::setPos(QPoint const &pos)
{
    _pos = pos;
}

void    QSFMLCanvas::setFrameTime(UInt32 frameTime)
{
    _frameTime = frameTime;
}

void QSFMLCanvas::onInit()
{

}

void QSFMLCanvas::onUpdate()
{

}

QPaintEngine* QSFMLCanvas::paintEngine() const
{
    return 0;
}

void QSFMLCanvas::showEvent(QShowEvent*)
{
    if (!_initialized)
    {
        #ifdef Q_WS_X11
        XFlush(QX11Info::display());
        #endif

        Create(winId());

        onInit();

        connect(&_timer, SIGNAL(timeout()), this, SLOT(repaint()));
        _timer.start();

        _initialized = true;
    }
}

void QSFMLCanvas::paintEvent(QPaintEvent*)
{
    onUpdate();

    Display();
}
