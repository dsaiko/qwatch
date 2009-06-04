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
 * Definition of Time Zones provider
 */

#ifndef TIMEZONES_H
#define TIMEZONES_H

#include <QString>
#include <QList>
#include <QDateTime>
#ifdef Q_OS_WIN
#include <qt_windows.h>

#endif

#ifdef Q_OS_WIN

typedef struct tagTZREG {
    LONG bias;
    LONG standardBias;
    LONG daylightBias;
    SYSTEMTIME standardDate;
    SYSTEMTIME daylightDate;
} TZIREG;

typedef struct _TimeZone {
    QString displayName;
    TIME_ZONE_INFORMATION *timeZoneInformation;

} TimeZone;


#endif

class TimeZones {
    public:
        TimeZones();
        ~TimeZones();
        QList<QString> * listTimeZones();
        QDateTime getLocalTime(QString timezone);

#ifdef Q_OS_WIN
        QList<TimeZone*> *timeZoneList;
#endif

};

#endif //TIMEZONES_H
