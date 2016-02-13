/***************************************************************************************
 *
 * This program helps you to manage your scores at darts.
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
#include "newmatchdialog.h"
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
    connect(this, SIGNAL(currentCellChanged(int,int,int,int)), this, SLOT(cellClickedReaction(int,int,int,int)));
    connect(this, SIGNAL(legWon(Player*)), ((MainWidget*)parent)->getMatchProgressWidget(), SLOT(legWon(Player*)));
    connect(this, SIGNAL(setWon(Player*)), ((MainWidget*)parent)->getMatchProgressWidget(), SLOT(setWon(Player*)));
}

void ScoreBoardWidget::newMatch(bool)
{
    NewMatchDialog dialog;
    if(dialog.exec() == QDialog::Accepted) {

        if(match != 0) {
            delete match;
        }
        match = new Match(dialog.getNLegsToWinSet(), dialog.getNSetsToWinMatch(), dialog.getDoubleOut());

        ((MainWidget*)parentWidget())->getMatchProgressWidget()->setNSets(dialog.getNSetsToWinMatch());

        setRowCount(0);
        setColumnCount(0);
    }
}

void ScoreBoardWidget::newPlayer(bool)
{
    bool ok;
    QString name = QInputDialog::getText(this, "New Player", "Player name:", QLineEdit::Normal, "", &ok);

    if(ok && !name.isEmpty()) {
        int nPlayers = match->getNPlayers();
        match->addPlayer(name);
        connect(this, SIGNAL(legWon(Player*)), match->playerAt(nPlayers), SLOT(legWin(Player*)));
        connect(this, SIGNAL(setWon(Player*)), match->playerAt(nPlayers), SLOT(setWin(Player*)));
        ((MainWidget*)parentWidget())->getMatchProgressWidget()->addPlayer(match->playerAt(nPlayers));

        if(nPlayers > 0) {
            insertColumn(2*nPlayers+1);
            insertColumn(2*nPlayers+2);
        } else {
            setRowCount(2+spacingAboveStats+statsTotalRowCount);
            setColumnCount(3);

            QTableWidgetItem* item = new QTableWidgetItem("average (leg)");
            item->setFont(QFont("Times", 10, QFont::Bold));
            setItem(rowCount()-statsAverageLegRowCountFromBottom, 0, item);

            item = new QTableWidgetItem("average (set)");
            item->setFont(QFont("Times", 10, QFont::Bold));
            setItem(rowCount()-statsAverageSetRowCountFromBottom, 0, item);

            item = new QTableWidgetItem("average (match)");
            item->setFont(QFont("Times", 10, QFont::Bold));
            setItem(rowCount()-statsAverageMatchRowCountFromBottom, 0, item);
        }
        QTableWidgetItem* iName = new QTableWidgetItem(name);
        iName->setFont(QFont("Times", 10, QFont::Bold));
        setItem(0, 2*nPlayers+1, iName);

        QTableWidgetItem* iScore = new QTableWidgetItem(QString::number(match->getPlayers().last()->getScore()));
        setItem(1, 2*nPlayers+1, iScore);

        QTableWidgetItem* iDetail = new QTableWidgetItem("");
        setItem(1, 2*nPlayers+2, iDetail);

        QTableWidgetItem* iAverageLeg = new QTableWidgetItem("");
        setItem(rowCount()-statsAverageLegRowCountFromBottom, 2*nPlayers+1, iAverageLeg);

        QTableWidgetItem* iAverageSet = new QTableWidgetItem("");
        setItem(rowCount()-statsAverageSetRowCountFromBottom, 2*nPlayers+1, iAverageSet);

        QTableWidgetItem* iAverageMatch = new QTableWidgetItem("");
        setItem(rowCount()-statsAverageMatchRowCountFromBottom, 2*nPlayers+1, iAverageMatch);
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
    if(player->getScore() == 0 && !match->isValidFinalShot(shot)) {
        currentMove->invalidate();
    }

    if(currentMove->isComplete() || !currentMove->isValid() || player->getScore() == 0) {
        insertRowIfNecessary(player);

        QTableWidgetItem* iScore = new QTableWidgetItem(QString::number(player->getScore()));
        setItem(nMoves+1, colIndex, iScore);

        QTableWidgetItem* iDetail = new QTableWidgetItem("");
        setItem(nMoves+1, colIndex+1, iDetail);

        updateStats(colIndex, player);
    }

    if(player->getScore() == 0) {
        resetTable(player->getNMoves());
        if(player->getNLegWinsForCurrentSet() == match->getNLegsToWinSet()-1) {
            emit setWon(player);
        } else {
            emit legWon(player);
        }
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

void ScoreBoardWidget::updateStats(int colIndex, Player *player)
{
    QString avgLeg = QString::number(player->averageLeg(), 'f', 1);
    QString avgSet = QString::number(player->averageSet(), 'f', 1);
    QString avgMatch = QString::number(player->averageMatch(), 'f', 1);

    if(avgLeg == "nan") {
        avgLeg = "";
    }
    if(avgSet == "nan") {
        avgSet = "";
    }
    if(avgMatch == "nan") {
        avgMatch = "";
    }

    item(rowCount()-statsAverageLegRowCountFromBottom, colIndex)->setText(avgLeg);
    item(rowCount()-statsAverageSetRowCountFromBottom, colIndex)->setText(avgSet);
    item(rowCount()-statsAverageMatchRowCountFromBottom, colIndex)->setText(avgMatch);
}

void ScoreBoardWidget::cellClickedReaction(int i, int j, int, int)
{
    if(i == 0 && j%2 == 1) {
        disconnect(((MainWidget*)parentWidget())->getBoardWidget(), SIGNAL(newShot(Shot*)), this, SLOT(newShot(Shot*)));
        connect(((MainWidget*)parentWidget())->getBoardWidget(), SIGNAL(newShot(Shot*)), this, SLOT(newShot(Shot*)));
    } else {
        disconnect(((MainWidget*)parentWidget())->getBoardWidget(), SIGNAL(newShot(Shot*)), this, SLOT(newShot(Shot*)));
    }
}

void ScoreBoardWidget::resetTable(int nmoves)
{
    for(int i=0; i<nmoves; ++i) {
        removeRow(2);
    }

    for(int i=0; i<match->getNPlayers(); ++i) {
        item(rowCount()-statsAverageLegRowCountFromBottom, 2*i+1)->setText("");
        item(1, 2*i+2)->setText("");
    }
}

void ScoreBoardWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left) {

        if(currentRow() == 0 && currentColumn()%2 == 1) {
            setCurrentCell(0, ((currentColumn()/2-1+match->getNPlayers())%match->getNPlayers())*2+1);
        }
    } else if(event->key() == Qt::Key_Right) {

        if(currentRow() == 0 && currentColumn()%2 == 1) {
            setCurrentCell(0, ((currentColumn()/2+1)%match->getNPlayers())*2+1);
        }
    } else if(event->key() == Qt::Key_Delete) {

        if(currentColumn() > 0 && currentColumn()%2 == 0) {
            Player* player = match->playerAt((currentColumn()-1)/2);
            if(currentRow() == player->getNMoves()) {
                Move* lastMove = player->takeLastMove();
                if(lastMove->isComplete()) {
                    item(currentRow()+1, currentColumn()-1)->setText("");
                    updateStats(currentColumn()-1, player);
                }
                item(currentRow(), currentColumn())->setText("");
                setCurrentCell(0, currentColumn()-1);
            }
        }
    }
}
