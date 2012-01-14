#ifndef WAITWIDGET_H
#define WAITWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QDesktopWidget>

class WaitWidget : public QWidget
{
public:
    WaitWidget();
    ~WaitWidget();

protected:
    virtual void    paintEvent(QPaintEvent *p);
};

#endif // WAITWIDGET_H
