#include <QApplication>
#include "MyCanvas.h"
#include "AnimatedImage.h"
#include "ListenServer.h"
#include "Exception.h"
#include "GameManager.h"
#include <QFile>
#include "ConfLoader.hpp"

int main(int ac, char **av)
{
    try {
        QApplication app(ac, av);

        const ConfObject  *obj = ConfLoader::getInstance()->getConfObjectFor("./config");

        ListenServerSingleton::getInstance()->init(obj->getStringValueOf("ip_server").c_str());
        ListenServerSingleton::getInstance()->start();

        QFile fileStyle("./rtypeStyle.css");

        if (fileStyle.open(QIODevice::ReadOnly))
        {
            app.setStyleSheet(fileStyle.readAll());
            fileStyle.close();
        }
        GameManager gameManager;

        gameManager.show();

        return app.exec();
    } catch (Exception *e) {
        LOGERR << "Program terminated with " << e->what() << std::endl;
    } catch (Exception e) {
        LOGERR << "Program terminated with " << e.what() << std::endl;
    }
    return (0);
}
