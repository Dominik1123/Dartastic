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

#include "set.h"

Set::Set()
{
    newLeg();
}

double Set::average()
{
    double sum=0;
    int nmoves=0;
    for(int i=0; i<legs.size(); ++i) {
        sum += legs.at(i)->average()*legs.at(i)->getNMoves();
        nmoves += legs.at(i)->getNMoves();
    }
    return sum/nmoves;
}

int Set::getNMoves()
{
    int nmoves = 0;
    for(int i=0; i<legs.size(); ++i) {
        nmoves += legs.at(i)->getNMoves();
    }
    return nmoves;
}

Leg* Set::currentLeg()
{
    return legs.last();
}

void Set::newLeg()
{
    legs.append(new Leg);
}
