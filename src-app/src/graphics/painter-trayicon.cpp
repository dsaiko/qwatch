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

void ClockPainter::paintTrayIcon(QWatch *app, QPainter *painter, QTime time, int size) {
    paintClock(app,painter,time,size,app->secondClockTimeDifferenceInSeconds,true);
    if(app->alarmAnimation->isRunning) {
        static QImage bellImg(":/alarm.png");
        //QRectF target(-TRAYICON_PIXMAP_SIZE/2, -TRAYICON_PIXMAP_SIZE/2, TRAYICON_PIXMAP_SIZE/2, TRAYICON_PIXMAP_SIZE/2);
        QRectF target(-50, -50, 150, 150);
        QRectF source(0.0, 0.0, bellImg.width(), bellImg.height());
        painter->drawImage(target, bellImg, source);
    }
}



