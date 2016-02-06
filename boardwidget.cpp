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

#include <QPainter>
#include <QPixmap>
#include <QSize>
#include <QSizePolicy>
#include <QStyle>
#include <QStyleOption>
#include <QtGlobal>
#include <QtMath>
#include "boardwidget.h"
#include "mainwidget.h"

BoardWidget::BoardWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(945, 945);
}

BoardWidget::~BoardWidget()
{
}

void BoardWidget::paintEvent(QPaintEvent *e)
{
    int w = qMin(size().width(), size().height());
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(".\\..\\Dartastic\\img\\dartboard2.png").scaled(QSize(w,w)));
    QWidget::paintEvent(e);
}

void BoardWidget::mousePressEvent(QMouseEvent *event)
{
    double size = qMin(width(), height());
    double scale = size/REF_SIZE_PX;
    double center = size/2;
    double r_bull = REF_R_BULL_PX*scale;
    double r_outerbull = REF_R_OUTERBULL_PX*scale;
    double r_innertriple = REF_R_INNERTRIPLE_PX*scale;
    double r_outertriple = REF_R_OUTERTRIPLE_PX*scale;
    double r_innerdouble = REF_R_INNERDOUBLE_PX*scale;
    double r_outerdouble = REF_R_OUTERDOUBLE_PX*scale;

    double dx=event->x()-center;
    double dy=event->y()-center;

    double r = qSqrt( dx*dx + dy*dy );
    double phi;
    if(dx >= 0 && dy < 0) {  // right upper quadrant;

        phi = RAD_TO_DEG*qAtan(dx/-dy);

    } else if(dx >= 0 && dy >= 0) {  // right lower quadrant;

        phi = 90 + RAD_TO_DEG*qAtan(dy/dx);

    } else if(dx < 0 && dy >= 0) {  // left lower quadrant;

        phi = 180 + RAD_TO_DEG*qAtan(-dx/dy);

    } else if(dx < 0 && dy < 0) {  // left upper quadrant;

        phi = 270 + RAD_TO_DEG*qAtan(dy/dx);

    }

    int number;
    if(phi <= 9) {
        number = 20;
    } else if(phi <= 9+18) {
        number = 1;
    } else if(phi <= 9+2*18) {
        number = 18;
    } else if(phi <= 9+3*18) {
        number = 4;
    } else if(phi <= 9+4*18) {
        number = 13;
    } else if(phi <= 9+5*18) {
        number = 6;
    } else if(phi <= 9+6*18) {
        number = 10;
    } else if(phi <= 9+7*18) {
        number = 15;
    } else if(phi <= 9+8*18) {
        number = 2;
    } else if(phi <= 9+9*18) {
        number = 17;
    } else if(phi <= 9+10*18) {
        number = 3;
    } else if(phi <= 9+11*18) {
        number = 19;
    } else if(phi <= 9+12*18) {
        number = 7;
    } else if(phi <= 9+13*18) {
        number = 16;
    } else if(phi <= 9+14*18) {
        number = 8;
    } else if(phi <= 9+15*18) {
        number = 11;
    } else if(phi <= 9+16*18) {
        number = 14;
    } else if(phi <= 9+17*18) {
        number = 9;
    } else if(phi <= 9+18*18) {
        number = 12;
    } else if(phi <= 9+19*18) {
        number = 5;
    } else {
        number = 20;
    }

    Shot* shot;

    if(r <= r_bull) {
        shot = new Shot("bull", 50);
    } else if(r <= r_outerbull) {
        shot = new Shot("outer", 25);
    } else if(r <= r_innertriple) {
        shot = new Shot(QString("  %1").arg(QString::number(number)), number);
    } else if(r <= r_outertriple) {
        shot = new Shot(QString("3x%1").arg(QString::number(number)), 3*number);
    } else if(r <= r_innerdouble) {
        shot = new Shot(QString("  %1").arg(QString::number(number)), number);
    } else if(r <= r_outerdouble) {
        shot = new Shot(QString("2x%1").arg(QString::number(number)), 2*number);
    } else {
        shot = new Shot("miss", 0);
    }

    emit newShot(shot);
}
