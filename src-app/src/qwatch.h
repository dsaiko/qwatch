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
 */

#ifndef QWATCH_H
#define QWATCH_H

#include <QtGui>
#include <QRect>
#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QIcon>
#include <QPainter>
#include <QRgb>
#include <QPalette>
#include <QSettings>
#include <QRadialGradient>
#include <QPointer>

#include "graphics/painter.h"
#include "config/configuration.h"
#include "menu/second-timezone.h"
#include "menu/set-alarmclock.h"
#include "menu/calendar.h"
#include "menu/about.h"
#ifdef Q_OS_WIN
#include "menu/update.h"
#endif
#include "timezones.h"
#include "graphics/alarmanimation.h"


#ifdef INTERSHOP
#define STR_APPTITLE            "ISWatch"
#else
#define STR_APPTITLE            "QWatch"
#endif

class QWatch : public QWidget
{
    Q_OBJECT

public:
    QWatch(QWidget *parent = 0);

public slots:
    //show/hide clock
    void showClock();
    void showClock(QSystemTrayIcon::ActivationReason reason);
    void hideClock();
    void setFramelessWindow();

    //update tray icon painting
    void updateTrayIcon();

    //display configuration for second timezone
    void displaySecondTimeZoneDialog();

    //display simple calendar
    void displayCalendar();

#ifdef Q_OS_WIN
    void updateApplication();
    void autoUpdateApplication();
#endif

    //display about dialog
    void displayAbout();


    //timer for updating second clock timezone difference
    void updateSecondClockTimeDifferenceTimer();
    void updateSecondClockTimeDifference();

    //timer to resets the windows frameless mode if composite manager is not running
    void checkFramelessMode();

    //set widget transparency
    void setTransparency(QAction *action);

    //aarmclock menu slots
    void enableAlarmClock();
    void displayAlarmClockDialog();
    void alarmTimeChanged(QTime t, bool readConfiguration = FALSE);

    void switchLanguage(QAction *action);
    void setClockSize(QAction *action);

protected:
    //paint watch
    void paintEvent(QPaintEvent *event);

    //move/drag widget
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    //init popup menu
    void initPopupMenu();

    //init and paint tray icon
    void initTray();
    void paintTrayIcon(QPainter *painter, QTime time, int size);


    QPoint mousePressPoint;
    QSystemTrayIcon *trayIcon;

    QMenu *popupMenu;
    QMenu *transparencyMenu;
    QAction *showAction;
    QAction *hideAction;
    QAction *framelessWindowAction;
    QAction *enableAlarmClockAction;
    QAction *stopAlarmClockAction;
    QAction *aboutAction;
    #ifdef Q_OS_WIN
    QAction *autoUpdateAction;
    #endif

    QTimer *timerSecondClockSynchronisation;
    QTime  alarmTime;
    QTimer *alarmTimer;
    AlarmAnimation *alarmAnimation;

    ClockPainter *clockPainter;
    Configuration *configuration;

    SecontTimeZoneDialog    *timeZoneDialog;
    SetAlarmClockDialog     *alarmClockDialog;
    AboutDialog             *aboutDialog;
    CalendarDialog          *calendarDialog;
    #ifdef Q_OS_WIN
    UpdateDialog            *updateDialog;
    #endif

    TimeZones               *timeZones;
    int secondClockTimeDifferenceInSeconds;
    int clockSize;

    virtual void changeEvent(QEvent *event);

    QTranslator *qtTranslator;
    QTranslator *appTranslator;
    void retranslateUi();

    QMap<QString,QObject *>   *translateMap;

    friend class ClockPainter;
    friend class AlarmAnimation;
    friend class QWatchTests;
    friend class UpdateDialog;
};

#endif //QWATCH_H
