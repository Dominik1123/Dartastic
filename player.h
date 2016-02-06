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

#ifndef PLAYER_H
#define PLAYER_H

#include <move.h>
#include <set.h>
#include <QList>
#include <QObject>
#include <QString>

class Player : public QObject
{
    Q_OBJECT

private:
    int id;
    QString name;
    QList<Set*> sets;

public:
    explicit Player(int id, QString name, QObject* parent = 0);

    double averageLeg();
    Move* getCurrentMove();
    int getNMoves();
    int getScore();
    void newSet();

public slots:
};

#endif // PLAYER_H
