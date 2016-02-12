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

#include "mainwindow.h"
#include <QAction>
#include <QGridLayout>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    w = new MainWidget(this);
    this->setCentralWidget(w);

    QToolBar* toolbar = new QToolBar;
    QAction* newMatch = new QAction(QIcon(".\\..\\Dartastic\\img\\new_orange_48x48.png"), "new match", this);
    QAction* newPlayer = new QAction(QIcon(".\\..\\Dartastic\\img\\new_player_48x48.png"), "new player", this);

    connect(newMatch, SIGNAL(triggered(bool)), w->getScoreBoardWidget(), SLOT(newMatch(bool)));
    connect(newPlayer, SIGNAL(triggered(bool)), w->getScoreBoardWidget(), SLOT(newPlayer(bool)));

    toolbar->addAction(newMatch);
    toolbar->addAction(newPlayer);

    addToolBar(toolbar);
}

MainWindow::~MainWindow()
{

}
