#include <QtGui/QApplication>
#include "MyCanvas.h"

int main(int ac, char **av)
{
    QApplication app(ac, av);

    QFrame* MainFrame = new QFrame;
    MainFrame->setWindowTitle("Qt SFML");
    MainFrame->resize(800, 500);
    MainFrame->show();

    GameSingleton::getInstance()->loadBackground("background.png");
    MyCanvas* SFMLView = new MyCanvas(MainFrame, QPoint(0, 0), QSize(800, 800));

    SFMLView->show();

    return app.exec();
}
