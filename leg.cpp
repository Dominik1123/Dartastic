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

#include "leg.h"

Leg::Leg()
{
    newMove(new Move);
}

double Leg::average()
{
    return ((double)INITIAL_SCORE-(double)getScore())/(double)getNMoves();
}

Move* Leg::currentMove()
{
    if(moves.last()->isComplete() || !moves.last()->isValid()) {
        moves.append(new Move);
    }
    return moves.last();
}

int Leg::getNMoves()
{
    return moves.size();
}

void Leg::newMove(Move *move)
{
    moves.append(move);
}

int Leg::getScore()
{
    int score = INITIAL_SCORE;
    for(int i=0; i<moves.size(); ++i) {
        if(moves.at(i)->isValid()) {
            score -= moves.at(i)->getScore();
        }
    }
    return score;
}
