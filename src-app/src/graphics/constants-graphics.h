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
 * Constants
 */

#ifndef CONSTANTS_GRAPHICS_H
#define CONSTANTS_GRAPHICS_H

#include <QPoint>

#ifdef INTERSHOP
#define LOGO_DEFAULT "INTERSHOP"
#else
#define LOGO_DEFAULT "QWATCH"
#endif

#define PI 3.141592653589793

#define SHADOWFFSET 5.0

#define TRAYICON_PIXMAP_SIZE 48
#define SMALLCLOCKSIZE 50
#define SMALLCLOCKSIZE2 57

const QPoint hourHand[] = {
    QPoint(0, 20),
    QPoint(-4, 10),
    QPoint(-5, -53),
    QPoint(-9, -62),
    QPoint(0, -82),
    QPoint(9, -62),
    QPoint(5, -53),
    QPoint(4, 10),
};

const QPoint minuteHand[] = {
    QPoint(0, 20),
    QPoint(-3, 10),
    QPoint(-5, -40),
    QPoint(-9, -55),
    QPoint(0, -82),
    QPoint(9, -55),
    QPoint(5, -40),
    QPoint(3, 10),
};

 const QPoint secondsHand[] = {
    QPoint(3, 8),
    QPoint(0, 30),
    QPoint(-3, 8),
    QPoint(-2, -12),
    QPoint(0, -82),
    QPoint(2, -12)
};

static const QPoint hourHand2[] = {
    QPoint(0, 15),
    QPoint(-5, 10),
    QPoint(-7, -25),
    QPoint(-9, -35),
    QPoint(0, -50),
    QPoint(9, -35),
    QPoint(7, -25),
    QPoint(5, 10),
};
static const QPoint minuteHand2[] = {
    QPoint(0, 20),
    QPoint(-5, 15),
    QPoint(-7, -30),
    QPoint(-9, -55),
    QPoint(0, -75),
    QPoint(9, -55),
    QPoint(7, -30),
    QPoint(5, 15),
};

#endif // CONSTANTS_GRAPHICS_H
