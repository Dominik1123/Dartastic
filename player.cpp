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

#include "player.h"

Player::Player(int id, QString name, QObject *parent) : QObject(parent), id(id), name(name)
{
    newSet();
}

double Player::averageLeg()
{
    return sets.last()->currentLeg()->average();
}

Move* Player::getCurrentMove()
{
    return sets.last()->currentLeg()->currentMove();
}

int Player::getNMoves()
{
    return sets.last()->currentLeg()->getNMoves();
}

int Player::getScore()
{
    return sets.last()->currentLeg()->getScore();
}

void Player::newSet()
{
    sets.append(new Set);
}
