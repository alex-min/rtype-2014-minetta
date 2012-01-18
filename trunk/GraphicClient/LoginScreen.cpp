#include "LoginScreen.h"
#include "ListenServer.h"

LoginScreen::LoginScreen(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);

    _loginLabel.setText("Enter your login: ");
    _buttonOk.setText("Ok");
    _createGameButton.setText("Create a Game");
    _connectButton.setText("You can now access to the game room !");
    _login = "";
    _clientId = -1;

    _availibility.setVisible(false);
    _createGameButton.setVisible(false);
    _connectButton.setVisible(false);

    QDesktopWidget desktopWidget;
    QRect rect = desktopWidget.screenGeometry();

    setFixedSize(rect.width() / 2, rect.height() / 2);

    QRect newRect = geometry();

    newRect.setX(rect.width() / 2 - ((rect.width() / 2) / 2));
    newRect.setY(rect.height() / 2 - ((rect.height() / 2) / 2));

    _createGameScreen.setGeometry(newRect);

    _formLayout.setSpacing(10);
    _formLayout.addRow(&_loginLabel, &_loginLineEdit);
    _formLayout.addWidget(&_availibility);
    _formLayout.addWidget(&_createGameButton);
    _formLayout.addWidget(&_buttonOk);
    _formLayout.addWidget(&_connectButton);

    setLayout(&_formLayout);

    connect(&_buttonOk, SIGNAL(clicked()), this, SLOT(validLogin()));
    connect(&_connectButton, SIGNAL(clicked()), this, SIGNAL(validate()));
    connect(&_createGameButton, SIGNAL(clicked()), this, SLOT(createGame()));
    connect(ListenServerSingleton::getInstance(), SIGNAL(connected(bool,short)), this, SLOT(validation(bool,short)));
}

void    LoginScreen::resetField()
{
    _availibility.clear();
    _availibility.setVisible(false);
}

void    LoginScreen::createGame()
{
    _createGameScreen.show();
}

void    LoginScreen::validation(bool v, short id)
{
    if (v == true)
    {
        _availibility.clear();
        _availibility.setVisible(false);
        _createGameButton.setVisible(true);
        _connectButton.setVisible(true);
        _loginLabel.setVisible(false);
        _loginLineEdit.setVisible(false);
        _buttonOk.setVisible(false);
        _clientId = id;
    }
    else
    {
        _availibility.setVisible(true);
        _availibility.setText("Your login is not available !");
    }
}

std::string const &LoginScreen::getLogin() const
{
    return (_login);
}

void    LoginScreen::validLogin()
{
    _login = _loginLineEdit.text().toStdString();

    _loginLineEdit.clear();

    if (!_login.empty())
        ListenServerSingleton::getInstance()->sendConnect(_login);
}

LoginScreen::~LoginScreen()
{

}
