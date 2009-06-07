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
 * $Rev$
 * $Id$
 *
 * QWatch - analog watch with extended functionality
 * under GPL Licence
 *
 * Constants
 */

#ifndef CONSTANTS_CONFIG_H
#define CONSTANTS_CONFIG_H

#ifdef INTERSHOP
#ifdef Q_OS_WIN
#define CONFIG_FOLDER           "iswatch"
#else
#define CONFIG_FOLDER           ".iswatch"
#endif
#else
#ifdef Q_OS_WIN
#define CONFIG_FOLDER           "qwatch"
#else
#define CONFIG_FOLDER           ".qwatch"
#endif
#endif

#define CONFIG_SECONDTIMEZONE   "SecondTimeZone"
#define CONFIG_SECONDTIMEZONE_LABEL   "SecondTimeZoneLabel"
#define CONFIG_TRANSPARENCY     "Transparency"
#define CONFIG_FRAMELESSWINDOW  "FramelessWindow"
#define CONFIG_ENABLEALARM      "AlarmEnabled"
#define CONFIG_ALARMCLOCK       "AlarmClock"
#define CONFIG_CLOCKSIZE        "ClockSize"
#define CONFIG_LANGUAGE         "Language"
#ifdef Q_OS_WIN
    #define CONFIG_AUTOUPDATE       "AutoUpdateEnabled"
    #define CONFIG_LAST_UPDATE_CHECK "LastUpgradeCheck"
#endif

#endif // CONSTANTS_CONFIG_H
