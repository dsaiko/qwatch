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
#include <QImage>

#include "graphics/painter.h"
#include "graphics/constants-graphics.h"
#include "qwatch.h"

void ClockPainter::paintAlarmClock(QWatch *app, QPainter *painter, QTime time, int offsetx, int offsety) {

    painter->save();
    painter->translate(offsetx, offsety);

    static QColor pen1(100,100,100,255);
    painter->setPen(pen1);

    painter->setBrush(*gradient3);
    painter->drawEllipse(-SMALLCLOCKSIZE/2,-SMALLCLOCKSIZE/2,SMALLCLOCKSIZE,SMALLCLOCKSIZE);

    painter->save();

    painter->scale(0.28,0.28);
    if(app->enableAlarmClockAction->isChecked()) {
          static const QColor alarmRed(192,0,0,255);
          painter->setBrush(alarmRed);
    }
    static const QPen pen2(QColor(100,100,100,255));
    painter->setPen(pen2);
    drawHand(painter, 6.0 * (time.minute() + time.second() / 60.0), minuteHand2, 8, false);
    drawHand(painter, 30.0 * ((time.hour() + time.minute() / 60.0)), hourHand2, 8, false);

    painter->restore();

    for (int j = 0; j < 12; j++) {
        painter->drawLine(21, 0, 22, 0);
        painter->rotate(360/12);
    }

    painter->restore();
}



