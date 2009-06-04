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
 * Alarm animations
 */

#include <QtGui>

#include "graphics/alarmanimation.h"
#include "graphics/painter.h"
#include "graphics/constants-graphics.h"
#include "config/constants-config.h"
#include "qwatch.h"
#include "sound/sound.h"

AlarmAnimation::AlarmAnimation(QWatch *app) {
    this->app = app;
    timerAnimation = NULL;
    timerAlarm = NULL;
    isRunning = false;
}

AlarmAnimation::~AlarmAnimation() {
    if(timerAnimation != NULL) {
        timerAnimation->stop();
        delete timerAnimation;
        timerAnimation = NULL;
    }
    if(timerAlarm != NULL) {
        timerAlarm->stop();
        delete timerAlarm;
        timerAlarm = NULL;
    }
}

#define ANIMATIONINTERVAL 50
#define ALARMINTERVAL 1500

void AlarmAnimation::startAlarm() {
    if(timerAnimation != NULL) {
        timerAnimation->stop();
        delete timerAnimation;
        timerAnimation = NULL;
    }
    if(timerAlarm != NULL) {
        timerAlarm->stop();
        delete timerAlarm;
        timerAlarm = NULL;
    }

    if(app->enableAlarmClockAction->isEnabled() == false) return;

    isRunning = true;
    alarmAnimationStep = 0;
    countAnimation = 0;
    countAlarm1 = 0;
    countAlarm2 = 0;

    timerAnimation  = new QTimer(this);
    connect(timerAnimation, SIGNAL(timeout()), this, SLOT(repaint()));
    timerAnimation->start(ANIMATIONINTERVAL);

    timerAlarm  = new QTimer(this);
    connect(timerAlarm, SIGNAL(timeout()), this, SLOT(alarmSound()));
    timerAlarm->setSingleShot(true);
    alarmSound();

    app->updateTrayIcon();
    app->stopAlarmClockAction->setEnabled(true);
}

void AlarmAnimation::repaint() {

    alarmAnimationStep += 25;
    if(alarmAnimationStep > 255) alarmAnimationStep=0;

    app->repaint();

    countAnimation++;

    //stop alarm completly after 30 minutes
    if(countAnimation * ANIMATIONINTERVAL > 1000 * 60 * 30) {
        stopAlarm();
    }
}

void AlarmAnimation::alarmSound() {

    WavSound::playWav(":/alarm.wav");
    countAlarm1++;

    if(countAlarm1 * ALARMINTERVAL > 1000 * 15) {
        if(countAlarm2 > 5) {
            timerAlarm->start(1000 * 60 * 2);
        } else {
            timerAlarm->start(1000 * 45);
        }
        countAlarm1 = 0;
        countAlarm2++;
    } else {
        timerAlarm->start(ALARMINTERVAL);
    }
}

void AlarmAnimation::stopAlarm() {
    isRunning = false;
    app->stopAlarmClockAction->setEnabled(false);
    app->enableAlarmClockAction->setChecked(false);
    app->configuration->setInt(CONFIG_ENABLEALARM,0);

    if(timerAnimation != NULL) {
        timerAnimation->stop();
        delete timerAnimation;
        timerAnimation = NULL;
        app->repaint();
        app->updateTrayIcon();
    }

   if(timerAlarm != NULL) {
        timerAlarm->stop();
        delete timerAlarm;
        timerAlarm = NULL;
    }
}

