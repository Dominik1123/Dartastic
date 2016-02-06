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

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QStyle>
#include <QStyleOption>
#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    board = new BoardWidget(this);
    scoreboard = new ScoreBoardWidget(this);

    QHBoxLayout* hlayout = new QHBoxLayout;

    hlayout->addWidget(board, 1);
    hlayout->addWidget(scoreboard, 0);

    this->setLayout(hlayout);
}

BoardWidget* MainWidget::getBoardWidget()
{
    return board;
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
