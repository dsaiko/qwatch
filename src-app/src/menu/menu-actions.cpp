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
 * Menu actions
 */

#include "qwatch.h"
#include "version.h"
#include "config/constants-config.h"
#include "constants-app.h"

void QWatch::displaySecondTimeZoneDialog() {
    if( timeZoneDialog == NULL) {
       timeZoneDialog = new SecontTimeZoneDialog(this, timeZones, configuration);
       connect(timeZoneDialog, SIGNAL(timeZoneChanged()), this, SLOT(updateSecondClockTimeDifference()));
    }
    timeZoneDialog->setDefaults();
    timeZoneDialog->show();
}

void QWatch::displayCalendar() {
    if( calendarDialog == NULL) {
       calendarDialog = new CalendarDialog(this);
    }
    calendarDialog->ui->calendarWidget->showToday();
    calendarDialog->show();
}

void QWatch::displayAbout() {
    if( aboutDialog == NULL) {
       aboutDialog = new AboutDialog(this);
    }
    aboutDialog->show();
}


void QWatch::displayAlarmClockDialog() {
    if( alarmClockDialog == NULL) {
       alarmClockDialog = new SetAlarmClockDialog(this, configuration);
       connect(alarmClockDialog, SIGNAL(alarmTimeChanged(QTime)), this, SLOT(alarmTimeChanged(QTime)));
    }
    alarmClockDialog->setDefaults();
    alarmClockDialog->show();
}


void QWatch::enableAlarmClock() {
    int value = 1;
    if(enableAlarmClockAction->isChecked() == false) {
        value = 0;
        alarmAnimation->stopAlarm();
    } else {
        alarmTimeChanged(QTime::currentTime(), true);
    }
    configuration->setInt(CONFIG_ENABLEALARM,value);
}

void QWatch::showClock(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::DoubleClick) {
        if(showAction->isEnabled()) {
            showClock();
        } else {
            hideClock();
        }
    }
}

void QWatch::hideClock() {
    hide();
    showAction->setEnabled(true);
    hideAction->setEnabled(false);
}

void QWatch::setTransparency(QAction *action) {
    bool ok;

    int value = action->data().toInt(&ok);
    if(ok == false) value = 0;

    configuration->setInt(CONFIG_TRANSPARENCY,value);
    setWindowOpacity(1.0-value/100.0);
}


void QWatch::setFramelessWindow() {
    if(framelessWindowAction->isEnabled() == false) return;

    bool checked = framelessWindowAction->isChecked();

    setAttribute(Qt::WA_TranslucentBackground, checked);
    setAttribute(Qt::WA_NoSystemBackground, checked);
    setWindowFlags(checked ?  WINDOWS_FLAGS_FRAMELESS :  WINDOWS_FLAGS_FRAME);
    show();
    configuration->setInt(CONFIG_FRAMELESSWINDOW,checked ? 1 : 0);
}


void QWatch::alarmTimeChanged(QTime t, bool readConfiguration)
{
    if(alarmTimer != NULL) {
        alarmTimer->stop();
        delete alarmTimer;
    }

    if(readConfiguration) {
        QString time = configuration->getString(CONFIG_ALARMCLOCK,"12:00");
        QStringList l = time.split(":");
        int h = l[0].toInt();
        int m = l[1].toInt();
        alarmTime.setHMS(h,m,0,0);
    } else {
        alarmTime = t;
        enableAlarmClockAction->setChecked(true);
        configuration->setInt(CONFIG_ENABLEALARM,1);
    }

    //timer for next alarm
    alarmTimer = new QTimer(this);
    connect(alarmTimer, SIGNAL(timeout()), alarmAnimation, SLOT(startAlarm()));
    alarmTimer->setSingleShot(true);
    QTime ct = QTime::currentTime();
    int ch = ct.hour();
    if(ch > 12) {
        ch -= 12;
    }
    if(ch == 0) {
        ch = 12;
    }

    int c = ch*60*60 + ct.minute() * 60 + ct.second();
    int a = alarmTime.hour()*60*60 + alarmTime.minute()*60 + alarmTime.second();

    if(a < c) a += 12*60*60;

    int nextAlarmStart = (a - c)*1000;

    alarmTimer->start(nextAlarmStart);
}


void QWatch::setClockSize(QAction *action) {
    bool ok;

    int size = action->data().toInt(&ok);
    if(ok == false) size = -1;

    if(size<1 || size>6) size=1;

    configuration->setInt(CONFIG_CLOCKSIZE,size);

    switch(size) {
        case 1:
            clockSize = 150;
            break;
        case 3:
            clockSize = 250;
            break;
        case 4:
            clockSize = 400;
            break;
        case 5:
            clockSize = 650;
            break;
        case 6: {
            QRect screen = QApplication::desktop()->geometry();            
            clockSize = screen.width() < screen.height() ? screen.width() : screen.height();
            break;
        }
        default:
            clockSize = 200;
    }

    clockPainter->createGradient();
    setFixedSize(clockSize, clockSize);
}

void QWatch::switchLanguage(QAction *action)
{
    QString lang = action->data().toString();

    configuration->setString(CONFIG_LANGUAGE,lang);

    qtTranslator->load("qt_" + lang, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    appTranslator->load("qwatch_" + lang,":/translations");
}


void QWatch::retranslateUi()
{
    if(calendarDialog != NULL) { calendarDialog->ui->retranslateUi(calendarDialog); }
    if(timeZoneDialog != NULL) { timeZoneDialog->ui->retranslateUi(timeZoneDialog); }
    if(alarmClockDialog != NULL) { alarmClockDialog->ui->retranslateUi(alarmClockDialog); }
#ifdef Q_OS_WIN
    if(updateDialog!=NULL) { updateDialog->ui->retranslateUi(updateDialog); }
#endif
    if(aboutDialog != NULL)    {
        aboutDialog->ui->retranslateUi(aboutDialog);
        QString html = aboutDialog->ui->textBrowser_2->toHtml().replace("VERSIONINFO",getVersion());
        #ifdef INTERSHOP
            html=html.replace("QWatch",QString("Intershop ")+STR_APPTITLE);
        #endif
        aboutDialog->ui->textBrowser_2->setHtml(html);
    }
    if(calendarDialog != NULL) { calendarDialog->ui->retranslateUi(calendarDialog); }


    QMapIterator<QString, QObject *> i(*translateMap);
    while (i.hasNext()) {
        i.next();
        QObject *o = i.value();
        QAction *action = dynamic_cast<QAction *>(o);
        QMenu   *menu = dynamic_cast<QMenu *>(o);
        if(action != NULL) {
            action->setText(QApplication::translate("QWatchMenu", i.key().toLatin1()));
        }
        if(menu != NULL) {
            menu->setTitle(QApplication::translate("QWatchMenu", i.key().toLatin1()));
        }
    }

    aboutAction->setText(aboutAction->text()+" "+STR_APPTITLE+" "+getVersion());
}


#ifdef Q_OS_WIN
void QWatch::updateApplication() {
    if( updateDialog == NULL) {
       updateDialog = new UpdateDialog(this);
    }
    updateDialog->show();
    updateDialog->init();
}

void QWatch::autoUpdateApplication() {
    configuration->setInt(CONFIG_AUTOUPDATE,autoUpdateAction->isChecked() ? 1 : 0);
}
#endif
