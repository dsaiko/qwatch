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
 * $Rev$
 * $Id$
 *
 * QWatch - analog watch with extended functionality
 * under GPL Licence
 *
 * Clock painting functions
 */

#ifndef PAINTER_H
#define PAINTER_H

#include <QDialog>
#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QIcon>
#include <QPainter>
#include <QPalette>
#include <QSettings>
#include <QRadialGradient>

class QWatch;

class ClockPainter {

public:
    void paintClock(QWatch *app, QPainter *painter, QTime time, int size, int secondtimeoffset, bool trayiconmode=false);
    void paintTrayIcon(QWatch *app, QPainter *painter, QTime time, int size);
    ClockPainter(QWatch *app);
    ~ClockPainter();
    void createGradient();


private:
    void paintDate(QPainter *painter);
    void paintStripes(QPainter *painter);
    void paintSecondClock(QPainter *painter, QTime time, int offsetx, int offsety);
    void paintAlarmClock(QWatch *app, QPainter *painter, QTime time, int offsetx, int offsety);
    void drawHand(QPainter *painter, double alfa, const QPoint *points, int nPoints, bool shape);
    void paintLogo(QPainter *painter);
    void paintDigits(QPainter *painter,bool tayiconmode);

protected:
    QRadialGradient *gradient;
    QRadialGradient *gradient3;

    QWatch *app;

};

#endif // PAINTER_H
