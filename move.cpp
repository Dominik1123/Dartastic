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

#include "move.h"

Move::Move() : valid(true)
{
}

int Move::getScore()
{
    int score=0;
    for(int i=0; i<shots.size(); ++i) {
        score += shots.at(i)->getScore();
    }
    return score;
}

void Move::newShot(Shot *shot)
{
    shots.append(shot);
}

void Move::invalidate()
{
    valid = false;
}

bool Move::isComplete()
{
    return shots.size() == 3;
}

bool Move::isValid()
{
    return valid;
}

QString Move::print()
{
    QString s="";
    for(int i=0; i<shots.size(); ++i) {
        s.append(shots.at(i)->getDetail()+", ");
    }
    s.remove(s.size()-2, 2);
    return s;
}
