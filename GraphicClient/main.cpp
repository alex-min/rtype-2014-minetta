#include <QApplication>
#include "MyCanvas.h"
#include "AnimatedImage.h"
#include "ListenServer.h"
#include "Exception.h"
#include "GameManager.h"
#include <QFile>

int main(int ac, char **av)
{
    try {
        QApplication app(ac, av);

        ListenServerSingleton::getInstance()->start();

        QFile fileStyle("./rtypeStyle.css");

        if (fileStyle.open(QIODevice::ReadOnly))
        {
            app.setStyleSheet(fileStyle.readAll());
            fileStyle.close();
        }
        GameManager gameManager;

        gameManager.show();

        //            QFrame* MainFrame = new QFrame;
        //            MainFrame->setWindowTitle("Qt SFML");
        //            MainFrame->resize(800, 600);
        //            MainFrame->show();

        //            MyCanvas* SFMLView = new MyCanvas(MainFrame, QPoint(0, 0), QSize(800, 600), 20);

        //            SFMLView->UseVerticalSync(false);
        //            SFMLView->show();


        return app.exec();
    } catch (Exception *e) {
        LOGERR << "Program terminated with " << e->what() << std::endl;
    }
    return (0);
}
