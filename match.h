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

#ifndef MATCH_H
#define MATCH_H

#include "player.h"
#include "shot.h"
#include <QList>

class Match
{
private:
    QList<Player*> players;
    int nLegsToWinSet;
    int nSetsToWinMatch;
    bool doubleOut;

public:
    Match(int nLegsToWinSet, int nSetsToWinMatch, bool doubleOut);

    void addPlayer(QString name);
    int getNPlayers();
    QList<Player*> getPlayers();
    Player* playerAt(int i);
    int getNLegsToWinSet();
    int getNSetsToWinMatch();
    bool isValidFinalShot(Shot* shot);
};

#endif // MATCH_H
