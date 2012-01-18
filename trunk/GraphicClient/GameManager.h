#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QStackedLayout>
#include "LoginScreen.h"
#include "GamesList.h"
#include "MyCanvas.h"

class GameManager : public QWidget
{
    Q_OBJECT

public:
    GameManager();
    ~GameManager();

public slots:
    void swingToGames();
    void swingToGameCanvas(bool b);
    void enterGame();
    void comeBackToLoginScreen();
    void switchToGameList();

private:
    QStackedLayout      _stackLayout;
    LoginScreen         _loginScreen;
    MyCanvas            *_sfmlCanvas;
    GamesList           _gamesList;
};

#endif // GAMEMANAGER_H
