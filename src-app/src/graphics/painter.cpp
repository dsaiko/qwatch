/*
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
 * Copyright (C) 2009 Dusan Saiko dusan.saiko@gmail.com
 *
 * $Rev: 44 $
 *
 * QWatch - analog watch with extended functionality
 * under GPL Licence
 *
 * Clock painting functions
 */

#include <QtGui>

#include "graphics/painter.h"
#include "graphics/constants-graphics.h"
#include "qwatch.h"

ClockPainter::ClockPainter(QWatch *app) {
        gradient = NULL;
        gradient3 = NULL;
        this->app = app;

        createGradient();

}

void ClockPainter::createGradient()
{
    if(gradient != NULL) {
        delete gradient;
    }

    if(gradient3 != NULL) {
        delete gradient3;
    }

    gradient = new QRadialGradient(0.0,0.0,app->clockSize*0.5, 0.0, 0.0);

    gradient->setColorAt(0.0, QColor(255,255,255,255));
    gradient->setColorAt(0.1, QColor(255,255,255,224));
    gradient->setColorAt(0.80, QColor(162,191,255,224));
    gradient->setColorAt(0.90, QColor(64,98,64,224));
    gradient->setColorAt(0.93, QColor(255,255,255,255));
    gradient->setColorAt(1.0, QColor(192,192,192,255));


    gradient3 = new QRadialGradient(SMALLCLOCKSIZE/4, SMALLCLOCKSIZE/4, SMALLCLOCKSIZE/2);

    gradient3->setColorAt(0.0, QColor(255,255,255,132));
    gradient3->setColorAt(1.0, QColor(255,255,255,192));

}

ClockPainter::~ClockPainter() {
    delete gradient;
    delete gradient3;
}

void ClockPainter::drawHand(QPainter *painter, double alfa, const QPoint *points, int nPoints, bool shape) {
    painter->save();
    painter->rotate(alfa);
    if(shape) {
        int x = (int)(SHADOWFFSET * sin((alfa + 45)*PI/180.0));
        int y = (int)(SHADOWFFSET * cos((alfa + 45)*PI/180.0));
        painter->translate(x,y);
    }
    painter->drawConvexPolygon(points, nPoints);
    painter->restore();
}

