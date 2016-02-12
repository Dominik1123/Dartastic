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

#ifndef MATCHPROGRESSWIDGET_H
#define MATCHPROGRESSWIDGET_H

#include <player.h>
#include <QTableWidget>

class MatchProgressWidget : public QTableWidget
{
    Q_OBJECT

private:
    int nSets;
    int whichSet;
    int nPlayers;

public:
    explicit MatchProgressWidget(QWidget *parent = 0);

    void setNSets(int nSets);

signals:

public slots:
    void addPlayer(Player *player);
    void legWon(Player* player);
    void setWon(Player*player);
};

#endif // MATCHPROGRESSWIDGET_H
