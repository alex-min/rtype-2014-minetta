#ifndef GAMESLIST_H
#define GAMESLIST_H

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QGridLayout>
#include <list>
#include <map>
#include "SystemDefines.h"

class GamesList : public QWidget
{
    Q_OBJECT

signals:
void    changeToPreviousScreen();

public:
    GamesList(QWidget *parent = 0);
    bool    checkIfGameExist(QString const &gameName, UInt8 nbMaxPlayer, UInt8 nbPlayer) const;
    void    eraseAll();
    ~GamesList();

public slots:
    void    addGame(UInt8 nbPlayer, UInt8 nbMaxPlayer, QString const &gameName);
    void    joinGame();
    void    refresh();
    void    getBack();

private:
    QGridLayout     _gridLayout;
    QTableWidget     *_gameList;
    QPushButton     _joinButton;
    QPushButton     _refreshButton;
    QPushButton     _backButton;
    std::map< int, std::list< QTableWidgetItem* > >   _rowList;
};

#endif // GAMESLIST_H
