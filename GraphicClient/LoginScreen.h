#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QDesktopWidget>
#include "SystemDefines.h"
#include "CreateGameScreen.h"

class LoginScreen : public QWidget
{
    Q_OBJECT

signals:
    void    validate();

public:
    LoginScreen(QWidget *parent = 0);
    std::string const &getLogin() const;
    void    resetField();
    ~LoginScreen();

public slots:
    void    validLogin();
    void    validation(bool v, short id);
    void    createGame();

private:
    QFormLayout _formLayout;
    QLabel  _loginLabel;
    QLineEdit   _loginLineEdit;
    QPushButton _buttonOk;
    QPushButton _connectButton;
    QPushButton _createGameButton;
    std::string _login;
    UInt16      _clientId;
    QLabel      _availibility;
    CreateGameScreen    _createGameScreen;
};

#endif // LOGINSCREEN_H
