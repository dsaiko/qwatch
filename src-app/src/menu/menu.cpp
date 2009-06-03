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
 * Menu creation
 */

#include "qwatch.h"
#include "version.h"
#include "config/constants-config.h"

QAction *createMenuItem(QMap<QString,QObject *> *translateMap, QObject *parent, QString text, bool enabled, const char *signal, QObject *slotObject, const char *slot, bool checkable=false, QActionGroup *actionGroup = 0, int data = -1) {
    QAction *action = new QAction(QApplication::translate("QWatchMenu", text.toLatin1()), parent);

    translateMap->insert(text,action);

    action->setEnabled(enabled);

    if(signal != NULL && slotObject != NULL) {
        QObject::connect(action, signal, slotObject, slot);
    }

    if(checkable || actionGroup) {
        action->setCheckable(true);
    }

    if(actionGroup) {
        actionGroup->addAction(action);
    }

    if(data >= 0) {
        action->setData(data);
    }

    return action;
}

void QWatch::initPopupMenu()
{    

    translateMap = new QMap<QString,QObject *>();

    showAction
        = createMenuItem(translateMap, this, QT_TRANSLATE_NOOP("QWatchMenu","Show"), false, SIGNAL(triggered()), this, SLOT(showClock()));
    hideAction
        = createMenuItem(translateMap, this, QT_TRANSLATE_NOOP("QWatchMenu","Hide"), true, SIGNAL(triggered()), this, SLOT(hideClock()));

    QAction *quitAction
        = createMenuItem(translateMap, this, QT_TRANSLATE_NOOP("QWatchMenu","Quit"), true, SIGNAL(triggered()), qApp, SLOT(quit()));
    quitAction->setIcon(QIcon(":/exit.png"));

    QAction *secondClockAction
        = createMenuItem(translateMap, this, QT_TRANSLATE_NOOP("QWatchMenu","Second time zone"), true, SIGNAL(triggered()), this, SLOT(displaySecondTimeZoneDialog()));
    secondClockAction->setIcon(QIcon(":/clock.png"));

    QAction *calendarAction
        = createMenuItem(translateMap, this, QT_TRANSLATE_NOOP("QWatchMenu","Display calendar"), true, SIGNAL(triggered()), this, SLOT(displayCalendar()));
    calendarAction->setIcon(QIcon(":/calendar.png"));

    aboutAction
        = createMenuItem(translateMap, this, QString(QT_TRANSLATE_NOOP("QWatchMenu","About")), true, SIGNAL(triggered()), this, SLOT(displayAbout()));
    aboutAction->setIcon(QIcon(":/about.png"));


#ifdef Q_OS_WIN
    QAction *updateAction
        = createMenuItem(translateMap, this, QT_TRANSLATE_NOOP("QWatchMenu","Update application ..."), true, SIGNAL(triggered()), this, SLOT(updateApplication()));
    updateAction->setIcon(QIcon(":/update.png"));

    autoUpdateAction
        = createMenuItem(translateMap, this, QT_TRANSLATE_NOOP("QWatchMenu","Allow monthly query of application update"), true, SIGNAL(triggered()), this, SLOT(autoUpdateApplication()),true);
    autoUpdateAction->setChecked(configuration->getInt(CONFIG_AUTOUPDATE,1));
#endif

    QAction *alarmClockSettingsAction
        = createMenuItem(translateMap, this, QT_TRANSLATE_NOOP("QWatchMenu","Set alarm clock"), true, SIGNAL(triggered()), this, SLOT(displayAlarmClockDialog()));
    alarmClockSettingsAction->setIcon(QIcon(":/alarm.png"));

    stopAlarmClockAction
        = createMenuItem(translateMap, this, QT_TRANSLATE_NOOP("QWatchMenu","Stop alarm!"), true, SIGNAL(triggered()), alarmAnimation, SLOT(stopAlarm()));
    stopAlarmClockAction->setEnabled(false);
    stopAlarmClockAction->setIcon(QIcon(":/stop.png"));

    enableAlarmClockAction
        = createMenuItem(translateMap, this, QT_TRANSLATE_NOOP("QWatchMenu","Enable alarm clock"), true, SIGNAL(triggered()), this, SLOT(enableAlarmClock()), true);
    enableAlarmClockAction->setChecked(configuration->getInt(CONFIG_ENABLEALARM,0));

    framelessWindowAction
        = createMenuItem(translateMap, this, QT_TRANSLATE_NOOP("QWatchMenu","Allow frameless window"), true, SIGNAL(triggered()), this, SLOT(setFramelessWindow()), true);
    framelessWindowAction->setChecked(configuration->getInt(CONFIG_FRAMELESSWINDOW,1));
    setFramelessWindow();

    QActionGroup *transparencyGroup = new QActionGroup(this);

    QAction *transparencyMenu00
        = createMenuItem(translateMap, this, QT_TRANSLATE_NOOP("QWatchMenu","Fully opaque"), true, NULL, NULL, NULL, true, transparencyGroup,0);
    QAction *transparencyMenu10
        = createMenuItem(translateMap, this, "10%", true, NULL, NULL, NULL, true, transparencyGroup,10);
    QAction *transparencyMenu25
        = createMenuItem(translateMap, this, "25%", true, NULL, NULL, NULL, true, transparencyGroup,25);
    QAction *transparencyMenu50
        = createMenuItem(translateMap, this, "50%", true, NULL, NULL, NULL, true, transparencyGroup,50);
    QAction *transparencyMenu75
        = createMenuItem(translateMap, this, "75%", true, NULL, NULL, NULL, true, transparencyGroup,75);
    QAction *transparencyMenu90
        = createMenuItem(translateMap, this, "90%", true, NULL, NULL, NULL, true, transparencyGroup,90);
    connect(transparencyGroup, SIGNAL(triggered(QAction*)), this, SLOT(setTransparency(QAction*)));

    QActionGroup *sizeGroup = new QActionGroup(this);
    QAction *clockSizeSmall
        = createMenuItem(translateMap, this, QT_TRANSLATE_NOOP("QWatchMenu","Small"), true, NULL, NULL, NULL, true, sizeGroup,1);
    QAction *clockSizeMedium
        = createMenuItem(translateMap, this, QT_TRANSLATE_NOOP("QWatchMenu","Normal"), true, NULL, NULL, NULL, true, sizeGroup,2);
    QAction *clockSizeLarge
        = createMenuItem(translateMap, this, QT_TRANSLATE_NOOP("QWatchMenu","Large"), true, NULL, NULL, NULL, true, sizeGroup,3);
    QAction *clockSizeExtraLarge
        = createMenuItem(translateMap, this, QT_TRANSLATE_NOOP("QWatchMenu","Even bigger"), true, NULL, NULL, NULL, true, sizeGroup,4);
    QAction *clockSizeExtraLargeX
        = createMenuItem(translateMap, this, QT_TRANSLATE_NOOP("QWatchMenu","Extra large"), true, NULL, NULL, NULL, true, sizeGroup,5);
    QAction *clockSizeScreen
        = createMenuItem(translateMap, this, QT_TRANSLATE_NOOP("QWatchMenu","Screen size"), true, NULL, NULL, NULL, true, sizeGroup,6);
    connect(sizeGroup, SIGNAL(triggered(QAction*)), this, SLOT(setClockSize(QAction*)));


    QMenu *languageMenu = new QMenu(QT_TRANSLATE_NOOP("QWatchMenu","Language"),this);
    translateMap->insert("Language",languageMenu);
    languageMenu->setIcon(QIcon(":/flags.png"));
    QActionGroup *languagesGroup = new QActionGroup(this);
    connect(languagesGroup, SIGNAL(triggered(QAction *)),this, SLOT(switchLanguage(QAction *)));

    QDir translations(":/translations");
    QStringList fileNames = translations.entryList(QStringList("qwatch_*.qm"));
    for(int i=0; i<fileNames.size(); i++) {
        QString locale = fileNames[i];
        locale.remove(0, locale.indexOf('_') +1);
        locale.chop(3);

        QTranslator translator;
        translator.load(fileNames[i],translations.absolutePath());
        QString language = translator.translate("QWatchMenu","English");

        QAction *action = new QAction(language,this);
        action->setCheckable(true);
        action->setData(locale);

        languageMenu->addAction(action);
        languagesGroup->addAction(action);

        action->setIcon(QIcon(":/images/flags/flag-"+locale+".png"));

        if(QApplication::translate("QWatchMenu","English") == language) {
            action->setChecked(true);
        }
    }

    switch(configuration->getInt(CONFIG_CLOCKSIZE,2)) {
        case 2:
            clockSizeMedium->setChecked(true); break;
        case 3:
            clockSizeLarge->setChecked(true); break;
        case 4:
            clockSizeExtraLarge->setChecked(true); break;
        case 5:
            clockSizeExtraLargeX->setChecked(true); break;
        case 6:
            clockSizeScreen->setChecked(true); break;
        default:
            clockSizeSmall->setChecked(true); break;
    }

    switch(configuration->getInt(CONFIG_TRANSPARENCY,10)) {
        case 10:
            transparencyMenu10->setChecked(true); break;
        case 25:
            transparencyMenu25->setChecked(true); break;
        case 50:
            transparencyMenu50->setChecked(true); break;
        case 75:
            transparencyMenu75->setChecked(true); break;
        case 90:
            transparencyMenu90->setChecked(true); break;
        default:
            transparencyMenu00->setChecked(true); break;
    }


    transparencyMenu = new QMenu(QT_TRANSLATE_NOOP("QWatchMenu","Transparency"),this);
    translateMap->insert("Transparency",transparencyMenu);
    transparencyMenu->addAction(transparencyMenu00);
    transparencyMenu->addAction(transparencyMenu10);
    transparencyMenu->addAction(transparencyMenu25);
    transparencyMenu->addAction(transparencyMenu50);
    transparencyMenu->addAction(transparencyMenu75);
    transparencyMenu->addAction(transparencyMenu90);

    QMenu *clockSizeMenu = new QMenu(QT_TRANSLATE_NOOP("QWatchMenu","Clock size"),this);
    translateMap->insert("Clock size",clockSizeMenu);
    clockSizeMenu->setIcon(QIcon(":/resize.png"));
    clockSizeMenu->addAction(clockSizeSmall);
    clockSizeMenu->addAction(clockSizeMedium);
    clockSizeMenu->addAction(clockSizeLarge);
    clockSizeMenu->addAction(clockSizeExtraLarge);
    clockSizeMenu->addAction(clockSizeExtraLargeX);
    clockSizeMenu->addSeparator();
    clockSizeMenu->addAction(clockSizeScreen);

    popupMenu = new QMenu(this);
    popupMenu->addMenu(transparencyMenu);
    popupMenu->addAction(framelessWindowAction);
    popupMenu->addMenu(clockSizeMenu);
    popupMenu->addMenu(languageMenu);
    popupMenu->addSeparator();
    popupMenu->addAction(secondClockAction);
    popupMenu->addAction(calendarAction);
    popupMenu->addSeparator();
    popupMenu->addAction(enableAlarmClockAction);
    popupMenu->addAction(alarmClockSettingsAction);
    popupMenu->addAction(stopAlarmClockAction);
    #ifdef Q_OS_WIN
    popupMenu->addSeparator();
    popupMenu->addAction(updateAction);
    popupMenu->addAction(autoUpdateAction);
    #endif
    popupMenu->addSeparator();
    popupMenu->addAction(showAction);
    popupMenu->addAction(hideAction);
    popupMenu->addSeparator();
    popupMenu->addAction(aboutAction);
    popupMenu->addAction(quitAction);
}
