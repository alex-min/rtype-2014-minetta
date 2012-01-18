#include "GamesList.h"
#include "ListenServer.h"
#include <iostream>

GamesList::GamesList(QWidget *parent) : QWidget(parent)
{
    _gameList = new QTableWidget(0, 2);

    _gameList->setHorizontalHeaderItem(0, new QTableWidgetItem("Games"));
    _gameList->setHorizontalHeaderItem(1, new QTableWidgetItem("Players"));

    _joinButton.setText("Join");
    _refreshButton.setText("Refresh");
    _backButton.setText("Previous");

    _gridLayout.addWidget(_gameList, 0, 0);
    _gridLayout.addWidget(&_refreshButton, 0, 1, 1, 1, Qt::AlignTop);
    _gridLayout.addWidget(&_backButton, 1, 1, 1, 1, Qt::AlignTop);
    _gridLayout.addWidget(&_joinButton, 1, 0);

    setLayout(&_gridLayout);

    connect(&_refreshButton, SIGNAL(clicked()), this, SLOT(refresh()));
    connect(&_joinButton, SIGNAL(clicked()), this, SLOT(joinGame()));
    connect(&_backButton, SIGNAL(clicked()), this, SLOT(getBack()));
    connect(_gameList, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(joinGame()));
    connect(ListGameSlotSingleton::getInstance(), SIGNAL(newGame(UInt8,UInt8,QString)), this, SLOT(addGame(UInt8,UInt8,QString)));
}

void    GamesList::getBack()
{
    emit changeToPreviousScreen();
}

void    GamesList::joinGame()
{
    QTableWidgetItem *item = _gameList->currentItem();

    if (!item)
        return;

    ListenServerSingleton::getInstance()->joinGame(item->text().toStdString());
}

void    GamesList::eraseAll()
{
    std::map< int, std::list< QTableWidgetItem* > >::const_iterator it = _rowList.begin();

    for (; it != _rowList.end(); ++it)
    {
        std::list< QTableWidgetItem* > list = (*it).second;

        QTableWidgetItem *frontItem = list.front();
        QTableWidgetItem *backItem = list.back();

        _gameList->removeCellWidget(frontItem->row(), frontItem->column());
        _gameList->removeCellWidget(backItem->row(), frontItem->column());

        list.remove(frontItem);
        list.remove(backItem);

        delete frontItem;
        delete backItem;
    }

    _gameList->setRowCount(0);

    _rowList.clear();
}

bool    GamesList::checkIfGameExist(QString const &gameName, UInt8 nbMaxPlayer, UInt8 nbPlayer) const
{
    std::map< int, std::list< QTableWidgetItem* > >::const_iterator it = _rowList.begin();

    for (; it != _rowList.end(); ++it)
    {
        std::list< QTableWidgetItem* > list = (*it).second;

        if (list.front()->text() == gameName)
        {
            QTableWidgetItem *item = list.back();

            item->setText(QString::number(static_cast<int>(nbPlayer)) +
                          QString("/") +
                          QString::number(static_cast<int>(nbMaxPlayer)));
            return (true);
        }
    }

    return (false);
}

void    GamesList::addGame(UInt8 nbPlayer, UInt8 nbMaxPlayer, QString const &gameName)
{
    if (!checkIfGameExist(gameName, nbMaxPlayer, nbPlayer))
    {
        QTableWidgetItem *first = new QTableWidgetItem(gameName);
        QTableWidgetItem *second = new QTableWidgetItem(QString::number(static_cast<int>(nbPlayer)) +
                                                        QString("/") +
                                                        QString::number(static_cast<int>(nbMaxPlayer)));

        first->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        second->setFlags(Qt::NoItemFlags);

        _gameList->setRowCount(_gameList->rowCount() + 1);
        _gameList->setItem(_gameList->rowCount() -1, 0, first);
        _gameList->setItem(_gameList->rowCount() -1, 1, second);

        std::list<QTableWidgetItem*> l;

        l.push_back(first);
        l.push_back(second);

        _rowList[_gameList->rowCount() -1] = l;
    }
}

void    GamesList::refresh()
{
    ListenServerSingleton::getInstance()->requestGamesList();
}

GamesList::~GamesList()
{

}
