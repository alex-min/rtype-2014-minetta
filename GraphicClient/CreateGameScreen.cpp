#include "CreateGameScreen.h"
#include "ListenServer.h"

CreateGameScreen::CreateGameScreen(QWidget *parent) : QWidget(parent)
{
    setWindowModality(Qt::ApplicationModal);

    _labelName.setText("Game name :");
    _labelMap.setText("Map id :");
    _labelPlayer.setText("Player number :");
    _validButton.setText("Create");
    _cancelButton.setText("Cancel");
    _spinBoxMap.setMaximum(9);
    _spinBoxPlayer.setMaximum(4);

    _gridLayout.addWidget(&_labelName, 0, 0);
    _gridLayout.addWidget(&_lineEditName, 0, 1);

    _gridLayout.addWidget(&_labelMap, 1, 0);
    _gridLayout.addWidget(&_spinBoxMap, 1, 1);

    _gridLayout.addWidget(&_labelPlayer, 2, 0);
    _gridLayout.addWidget(&_spinBoxPlayer, 2, 1);

    _gridLayout.addWidget(&_validButton, 3, 0);
    _gridLayout.addWidget(&_cancelButton, 3, 1);

    setLayout(&_gridLayout);

    connect(&_validButton, SIGNAL(clicked()), this, SLOT(createGame()));
    connect(&_cancelButton, SIGNAL(clicked()), this, SLOT(giveUp()));
    connect(ListenServerSingleton::getInstance(), SIGNAL(gameCreation(bool)), this, SLOT(validGameCreation(bool)));
}

void    CreateGameScreen::validGameCreation(bool validation)
{
    setEnabled(true);

    if (validation == true)
    {
        QMessageBox::information(this, "Game creation confirmation", "The game is successfully created");
        close();
    }
    else
        QMessageBox::information(this, "Game creation confirmation", "The game failed to be created");
}

void    CreateGameScreen::createGame()
{
    if (_lineEditName.text().isEmpty() || _spinBoxPlayer.value() > 0)
    {
        char mapId = _spinBoxMap.value() + '0';
        char nbPlayers = _spinBoxPlayer.value() + '0';

        ListenServerSingleton::getInstance()->createGame(_lineEditName.text().toStdString(), mapId, nbPlayers);

        _lineEditName.clear();
        _spinBoxMap.clear();
        _spinBoxPlayer.clear();

        setEnabled(false);
    }
}

void    CreateGameScreen::giveUp()
{
    close();
}

CreateGameScreen::~CreateGameScreen()
{

}
