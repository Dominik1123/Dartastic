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

Match::Match()
{

}

void Match::addPlayer(QString name)
{
    players.append(new Player(players.size(), name));
}

int Match::getNPlayers()
{
    return players.size();
}

QList<Player*> Match::getPlayers()
{
    return players;
}

Player* Match::playerAt(int i)
{
    return players.at(i);
}