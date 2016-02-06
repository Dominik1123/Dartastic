/#######################################################################################
 #
 # This program solves the 2D puzzle "Lonpos 101".
 # Copyright (C) 2016  Dominik Vilsmeier
 #
 # This program is free software: you can redistribute it and/or modify
 # it under the terms of the GNU General Public License as published by
 # the Free Software Foundation, either version 3 of the License, or
 # (at your option) any later version.
 #
 # This program is distributed in the hope that it will be useful,
 # but WITHOUT ANY WARRANTY; without even the implied warranty of
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 # GNU General Public License for more details.
 #
 # You should have received a copy of the GNU General Public License
 # along with this program.  If not, see <http://www.gnu.org/licenses/>.
 #
 #######################################################################################/

#-------------------------------------------------
#
# Project created by QtCreator 2016-01-31T23:46:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Dartastic
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mainwidget.cpp \
    boardwidget.cpp \
    shot.cpp \
    player.cpp \
    scoreboardwidget.cpp \
    move.cpp \
    leg.cpp \
    set.cpp \
    match.cpp

HEADERS  += mainwindow.h \
    mainwidget.h \
    boardwidget.h \
    shot.h \
    player.h \
    scoreboardwidget.h \
    move.h \
    leg.h \
    set.h \
    match.h
