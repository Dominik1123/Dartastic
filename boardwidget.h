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

#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <shot.h>
#include <QList>
#include <QMouseEvent>
#include <QWidget>

class BoardWidget : public QWidget
{
    Q_OBJECT

private:
    static const int MIN_SIZE_PX=1000;

    static const double REF_SIZE_PX=945;
    static const double REF_CENTER_PX=472;
    static const double REF_R_BULL_PX=9;
    static const double REF_R_OUTERBULL_PX=24;
    static const double REF_R_INNERTRIPLE_PX=165;
    static const double REF_R_OUTERTRIPLE_PX=181;
    static const double REF_R_INNERDOUBLE_PX=277;
    static const double REF_R_OUTERDOUBLE_PX=292;
    static const double DELTA_PHI_DEG=18;
    static const double RAD_TO_DEG=57.29577951308232;

public:
    explicit BoardWidget(QWidget *parent = 0);
    ~BoardWidget();

signals:
    void newShot(Shot* shot);

public slots:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent* event);
};

#endif // BOARDWIDGET_H
