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

#include "mainwidget.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QStyle>
#include <QStyleOption>

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    board = new BoardWidget(this);
    matchprogress = new MatchProgressWidget(this);
    scoreboard = new ScoreBoardWidget(this);

    QHBoxLayout* hlayout = new QHBoxLayout;

    hlayout->addWidget(board, 1);

    QVBoxLayout* vlayout = new QVBoxLayout;
    vlayout->addWidget(scoreboard, 1);
    vlayout->addWidget(matchprogress, 0);

    hlayout->addLayout(vlayout, 0);

    this->setLayout(hlayout);
}

BoardWidget* MainWidget::getBoardWidget()
{
    return board;
}

MatchProgressWidget* MainWidget::getMatchProgressWidget()
{
    return matchprogress;
}

ScoreBoardWidget* MainWidget::getScoreBoardWidget()
{
    return scoreboard;
}

void MainWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
