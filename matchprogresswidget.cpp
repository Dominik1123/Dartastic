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

#include "matchprogresswidget.h"
#include <QFont>
#include <QHeaderView>
#include <QString>
#include <QTableWidgetItem>

MatchProgressWidget::MatchProgressWidget(QWidget *parent) : QTableWidget(parent)
{
    nSets=0;
    whichSet=1;
    nPlayers=0;

    horizontalHeader()->hide();
    verticalHeader()->hide();
}

void MatchProgressWidget::setNSets(int nSets)
{
    this->nSets = nSets;
    setColumnCount(nSets+1);
}

void MatchProgressWidget::addPlayer(Player* player)
{
    insertRow(nPlayers);
    QTableWidgetItem* iName = new QTableWidgetItem(player->getName());
    iName->setFont(QFont("Times", 10, QFont::Bold));
    setItem(nPlayers, 0, iName);

    for(int i=1; i<=nSets; ++i) {
        QTableWidgetItem *iLegs = new QTableWidgetItem("0");
        iLegs->setTextAlignment(Qt::AlignHCenter);
        setItem(nPlayers, i, iLegs);
    }
    nPlayers += 1;
}

void MatchProgressWidget::legWon(Player *player)
{
    int nLegs = item(player->getId(), whichSet)->text().toInt() + 1;
    item(player->getId(), whichSet)->setText(QString::number(nLegs));
}

void MatchProgressWidget::setWon(Player* player)
{
    legWon(player);
    whichSet += 1;
}
