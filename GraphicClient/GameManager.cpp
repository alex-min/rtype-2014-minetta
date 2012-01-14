#include "GameManager.h"
#include <iostream>
#include "ListenServer.h"

GameManager::GameManager()
{
    QDesktopWidget desktopWidget;
    QRect rect = desktopWidget.screenGeometry();

    setFixedSize(rect.width() / 2, rect.height() / 2);

    QRect newRect = geometry();

    newRect.setX(rect.width() / 2 - ((rect.width() / 2) / 2));
    newRect.setY(rect.height() / 2 - ((rect.height() / 2) / 2));

    setGeometry(newRect);

    QFrame* MainFrame = new QFrame;

    MainFrame->setWindowTitle("Qt SFML");
    MainFrame->resize(rect.width() / 2, rect.height() / 2);

    _sfmlCanvas = new MyCanvas(MainFrame, QPoint(0, 0), QSize(rect.width() / 2, rect.height() / 2), 20);

    _sfmlCanvas->UseVerticalSync(false);

    _stackLayout.addWidget(&_loginScreen);
    _stackLayout.addWidget(&_gamesList);
    _stackLayout.addWidget(_sfmlCanvas);

    setLayout(&_stackLayout);


    connect(&_loginScreen, SIGNAL(validate()), this, SLOT(swingToGames()));
    connect(&_gamesList, SIGNAL(changeToPreviousScreen()), this, SLOT(comeBackToLoginScreen()));
    connect(ListenServerSingleton::getInstance(), SIGNAL(gameAccess(bool)), this, SLOT(swingToGameCanvas(bool)));
    connect(ListenServerSingleton::getInstance(), SIGNAL(startGame()), this, SLOT(enterGame()));
}

void    GameManager::comeBackToLoginScreen()
{
    _stackLayout.setCurrentWidget(&_loginScreen);
}

void    GameManager::enterGame()
{
    _sfmlCanvas->setWaitingSprite(false);
}

void GameManager::swingToGameCanvas(bool b)
{
    if (b == true)
    {
        ListenServerSingleton::getInstance()->sendConnectUdp(_loginScreen.getLogin());
        _stackLayout.setCurrentWidget(_sfmlCanvas);
        _sfmlCanvas->setWaitingSprite(true);
    }
    else
        QMessageBox::information(this, "Join Game", "You can't join the game because the game has reached the limit player number.");
}

void GameManager:: swingToGames()
{
    _stackLayout.setCurrentWidget(&_gamesList);
    dynamic_cast<GamesList*>(_stackLayout.currentWidget())->refresh();
}

GameManager::~GameManager()
{
    //    delete _sfmlCanvas;
}
