#ifndef SCOREBOARDWIDGET_H
#define SCOREBOARDWIDGET_H

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

#include "match.h"
#include "player.h"
#include "shot.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QList>
#include <QPushButton>
#include <QTableWidget>
#include <QWidget>

class ScoreBoardWidget : public QTableWidget
{
    Q_OBJECT

private:
    Match* match;

    void insertRowIfNecessary(Player *player);

public:
    explicit ScoreBoardWidget(QWidget *parent = 0);

signals:

public slots:
    void newMatch(bool);
    void newPlayer(bool);
    void newShot(Shot* shot);
    void cellClickedReaction(int i, int j);
};

#endif // SCOREBOARDWIDGET_H
