#include "WaitWidget.h"
#include <iostream>

WaitWidget::WaitWidget()
{
    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(Qt::FramelessWindowHint);

    setMinimumSize(50, 50);

    QDesktopWidget desktopWidget;
    QRect rect = desktopWidget.screenGeometry();

    setFixedSize(rect.width() / 5, rect.height() / 5);

    QRect newRect = geometry();

    newRect.setX(rect.width() / 2 - ((rect.width() / 2) / 5));
    newRect.setY(rect.height() / 2 - ((rect.height() / 2) / 5));

    setGeometry(newRect);
    setObjectName("WaitWidget");
}

void    WaitWidget::paintEvent(QPaintEvent *p)
{
    QPainter    painter(this);
//    QTextOption option(Qt::AlignCenter);

    QWidget::paintEvent(p);

    painter.setPen(QColor(0, 0, 0));
    painter.drawRect(geometry());
    painter.drawText(geometry(), "Waiting guests..."/*, option*/);
}

WaitWidget::~WaitWidget()
{

}
