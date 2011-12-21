#ifndef QSFMLCANVAS_HPP
#define QSFMLCANVAS_HPP

#include <SFML/Graphics.hpp>
#include <Qt/qwidget.h>
#include <Qt/qtimer.h>

class QSFMLCanvas : public QWidget, public sf::RenderWindow
{
public :

    QSFMLCanvas(QWidget* parent, const QPoint& position, const QSize& size, unsigned int frameTime = 0);
    bool    isInitialized();
    QSize const &getScreenSize();
    QPoint const &getPos();
    unsigned int getFrameTime() const;
    void    setInitialized(bool init);
    void    setScreenSize(QSize const &size);
    void    setPos(QPoint const &pos);
    void    setFrameTime(unsigned int frameTime);
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
    unsigned int _frameTime;
};


#endif // QSFMLCANVAS_HPP
