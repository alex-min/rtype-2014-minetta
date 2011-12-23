#include <QtGui/QApplication>
#include "MyCanvas.h"
#include "AnimatedImage.h"

int main(int ac, char **av)
{
    QApplication app(ac, av);

    QFrame* MainFrame = new QFrame;
    MainFrame->setWindowTitle("Qt SFML");
    MainFrame->resize(1500, 800);
    MainFrame->show();

    MyCanvas* SFMLView = new MyCanvas(MainFrame, QPoint(0, 0), QSize(1500, 800), 20);

    SFMLView->UseVerticalSync(false);
    SFMLView->show();

    return app.exec();
}
