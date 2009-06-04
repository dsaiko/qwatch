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
 * $Rev: 35 $
 * $Id$
 *
 * QWatch - analog watch with extended functionality
 * under GPL Licence
 *
 * Alarm animations
 */

#ifndef ALARMANIMATION_H
#define ALARMANIMATION_H

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

class AlarmAnimation : public QObject {

    Q_OBJECT

public:
    AlarmAnimation(QWatch *app);
    ~AlarmAnimation();

public slots:
    void repaint();
    void alarmSound();
    void startAlarm();
    void stopAlarm();

protected:
    QWatch *app;
    QTimer *timerAnimation;
    QTimer *timerAlarm;
    int    alarmAnimationStep;
    bool   isRunning;
    int    countAnimation;
    int    countAlarm1, countAlarm2;

    friend class ClockPainter;
};

#endif // ALARMANIMATION_H
