#ifndef QSFMLCANVAS_HPP
#define QSFMLCANVAS_HPP

#include "Sfml.h"
#include <QWidget>
#include <QTimer>
#include "SystemDefines.h"

class QSFMLCanvas : public QWidget, public sf::RenderWindow
{
public :

    QSFMLCanvas(QWidget* parent, const QPoint& position, const QSize& size, UInt32 frameTime = 0);
    bool    isInitialized();
    QSize const &getScreenSize();
    QPoint const &getPos();
    UInt32 getFrameTime() const;
    void    setInitialized(bool init);
    void    setScreenSize(QSize const &size);
    void    setPos(QPoint const &pos);
    void    setFrameTime(UInt32 frameTime);
    virtual ~QSFMLCanvas();

private :

    virtual void onInit();
    virtual void onUpdate();
    virtual QPaintEngine* paintEngine() const;
    virtual void showEvent(QShowEvent*);
    virtual void paintEvent(QPaintEvent*);

protected:

    QTimer  _timer;
    bool   _initialized;
    QSize  _size;
    QPoint _pos;
    UInt32 _frameTime;
};


#endif // QSFMLCANVAS_HPP
