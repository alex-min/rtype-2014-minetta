#ifndef CREATEGAMESCREEN_H
#define CREATEGAMESCREEN_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QMessageBox>

class CreateGameScreen : public QWidget
{
    Q_OBJECT

public:
    CreateGameScreen(QWidget *parent = 0);
    ~CreateGameScreen();

public slots:
    void    createGame();
    void    giveUp();
    void    validGameCreation(bool validation);

private:

    QPushButton _validButton;
    QPushButton _cancelButton;
    QGridLayout _gridLayout;
    QLabel      _labelName;
    QLineEdit   _lineEditName;
    QLabel      _labelMap;
    QSpinBox    _spinBoxMap;
    QLabel      _labelPlayer;
    QSpinBox   _spinBoxPlayer;
};

#endif // CREATEGAMESCREEN_H
