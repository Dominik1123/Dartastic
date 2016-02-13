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

#include "player.h"

Player::Player(int id, QString name, QObject *parent) : QObject(parent), id(id), name(name)
{
    nLegWinsForCurrentSet=0;
    nSetWins=0;

    newSet();
}

int Player::getId()
{
    return id;
}

QString Player::getName()
{
    return name;
}

double Player::averageLeg()
{
    return sets.last()->currentLeg()->average();
}

double Player::averageSet()
{
    return sets.last()->average();
}

double Player::averageMatch()
{
    double sum=0;
    int nmoves=0;
    for(int i=0; i<sets.size(); ++i) {
        sum += sets.at(i)->average()*sets.at(i)->getNMoves();
        nmoves += sets.at(i)->getNMoves();
    }
    return sum/nmoves;
}

double Player::doubleRate()
{
    double sum=0;
    for(int i=0; i<doubleAttempts.size(); ++i) {
        sum += doubleAttempts.at(i);
    }
    return (sum/doubleAttempts.size())*100.;
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

void Player::legWin(Player *player)
{
    if(player == this) {
        nLegWinsForCurrentSet += 1;
    }
    sets.last()->newLeg();
}

void Player::setWin(Player *player)
{
    if(player == this) {
        nSetWins += 1;
    }
    nLegWinsForCurrentSet = 0;
    newSet();
}

int Player::getNLegWinsForCurrentSet()
{
    return nLegWinsForCurrentSet;
}

int Player::getNSetWins()
{
    return nSetWins;
}


Move* Player::takeLastMove()
{
    return sets.last()->currentLeg()->takeLastMove();
}

void Player::newDoubleAttempt(bool success)
{
    doubleAttempts.append(success);
}
