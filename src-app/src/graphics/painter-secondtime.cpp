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
 * $Id$
 *
 * QWatch - analog watch with extended functionality
 * under GPL Licence
 *
 * Clock painting functions
 */

#include <QtGui>

#include "graphics/painter.h"
#include "graphics/constants-graphics.h"


void ClockPainter::paintSecondClock(QPainter *painter, QTime time, int offsetx, int offsety) {
    painter->save();
    painter->translate(offsetx, offsety);

    static QColor pen1(100,100,100,255);
    static QColor pen2(100,100,100,255);
    static QColor brush1(255,255,255,255);
    painter->setPen(pen1);

    painter->setBrush(*gradient3);
    painter->drawEllipse(-SMALLCLOCKSIZE2/2,-SMALLCLOCKSIZE2/2,SMALLCLOCKSIZE2,SMALLCLOCKSIZE2);

    painter->save();

    painter->scale(0.32,0.32);
    painter->setBrush(brush1);
    painter->setPen(pen2);
    drawHand(painter, 6.0 * (time.minute() + time.second() / 60.0), minuteHand2, 8, false);
    drawHand(painter, 30.0 * ((time.hour() + time.minute() / 60.0)), hourHand2, 8, false);

    painter->restore();

    for (int j = 0; j < 12; j++) {
        painter->drawLine(24, 0, 25, 0);
        painter->rotate(360/12);
    }

    painter->restore();
}
