/***************************************************************************************
 *
 * This program solves the 2D puzzle "Lonpos 101".
 * Copyright (C) 2016  Dominik Vilsmeier
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ***************************************************************************************/

#include "scoreboardwidget.h"
#include "mainwidget.h"
#include "move.h"
#include <QFont>
#include <QIcon>
#include <QInputDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QWidget>

ScoreBoardWidget::ScoreBoardWidget(QWidget *parent) : QTableWidget(parent), match(0)
{
    newMatch(true);
    connect(this, SIGNAL(cellClicked(int,int)), this, SLOT(cellClickedReaction(int,int)));
}

void ScoreBoardWidget::newMatch(bool)
{
    if(match != 0) {
        delete match;
    }
    match = new Match;

    setRowCount(0);
    setColumnCount(0);
}

void ScoreBoardWidget::newPlayer(bool)
{
    bool ok;
    QString name = QInputDialog::getText(this, "New Player", "Player name:", QLineEdit::Normal, "", &ok);

    if(ok && !name.isEmpty()) {
        int nPlayers = match->getNPlayers();
        match->addPlayer(name);
        if(nPlayers > 0) {
            insertColumn(2*nPlayers+1);
            insertColumn(2*nPlayers+2);
        } else {
//            setRowCount(6);
            setRowCount(5);
            setColumnCount(3);

            QTableWidgetItem* item = new QTableWidgetItem("average (leg)");
            item->setFont(QFont("Times", 10, QFont::Bold));
            setItem(4, 0, item);

//            item = new QTableWidgetItem("average (set)");
//            item->setFont(QFont("Times", 10, QFont::Bold));
//            setItem(5, 0, item);
        }
        QTableWidgetItem* iName = new QTableWidgetItem(name);
        iName->setFont(QFont("Times", 10, QFont::Bold));
        setItem(0, 2*nPlayers+1, iName);

        QTableWidgetItem* iScore = new QTableWidgetItem(QString::number(match->getPlayers().last()->getScore()));
        setItem(1, 2*nPlayers+1, iScore);

        QTableWidgetItem* iDetail = new QTableWidgetItem("");
        setItem(1, 2*nPlayers+2, iDetail);

        QTableWidgetItem* iAverageLeg = new QTableWidgetItem("");
        setItem(4, 2*nPlayers+1, iAverageLeg);
    }
}

void ScoreBoardWidget::newShot(Shot *shot)
{
    int colIndex = currentColumn();
    Player* player = match->playerAt(colIndex/2);
    Move* currentMove = player->getCurrentMove();
    currentMove->newShot(shot);
    int nMoves = player->getNMoves();

    item(nMoves, colIndex+1)->setText(currentMove->print());

    if(player->getScore() < 0) {
        currentMove->invalidate();
    }

    if(currentMove->isComplete() || !currentMove->isValid() || player->getScore() == 0) {
        insertRowIfNecessary(player);

        QTableWidgetItem* iScore = new QTableWidgetItem(QString::number(player->getScore()));
        setItem(nMoves+1, colIndex, iScore);

        QTableWidgetItem* iDetail = new QTableWidgetItem("");
        setItem(nMoves+1, colIndex+1, iDetail);

        item(rowCount()-1, colIndex)->setText(QString::number(player->averageLeg(), 'f', 1));
    }
}

void ScoreBoardWidget::insertRowIfNecessary(Player* player)
{
    int nMoves = player->getNMoves();
    bool isFirst = true;
    QList<Player*> players = match->getPlayers();
    for(int i=0; i<players.size() && isFirst; ++i) {
        if(players.at(i) != player && players.at(i)->getNMoves() >= nMoves) {
            isFirst = false;
        }
    }

    if(isFirst) {
        insertRow(nMoves+1);
    }
}

void ScoreBoardWidget::cellClickedReaction(int i, int j)
{
    if(i == 0 && j%2 == 1) {
        disconnect(((MainWidget*)parentWidget())->getBoardWidget(), SIGNAL(newShot(Shot*)), this, SLOT(newShot(Shot*)));
        connect(((MainWidget*)parentWidget())->getBoardWidget(), SIGNAL(newShot(Shot*)), this, SLOT(newShot(Shot*)));
    } else {
        disconnect(((MainWidget*)parentWidget())->getBoardWidget(), SIGNAL(newShot(Shot*)), this, SLOT(newShot(Shot*)));
    }
}
