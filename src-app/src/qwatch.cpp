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

#include "qwatch.h"

#include "constants-app.h"
#include "config/constants-config.h"
#include "graphics/constants-graphics.h"
#include "systeminfo.h"
#include <QFile>
#include <QFileInfo>

#ifdef Q_OS_WIN
void deleteLocalSetupFiles() {
    QDir configFolder(Configuration::getSettingsFolder() + QDir::separator() + CONFIG_FOLDER);
    configFolder.mkdir(configFolder.absolutePath());

    QFileInfoList fileList = configFolder.entryInfoList();
    foreach(QFileInfo fileInfo, fileList) {
        if(fileInfo.isFile()) {
            QString filePath = fileInfo.absoluteFilePath();
            if(filePath.contains(QString(STR_APPTITLE).toLower()+"-") && filePath.endsWith("-setup.exe")) {
                qDebug() << "Deleting old setup file " << filePath;
                QFile setupFile(filePath);
                setupFile.remove();
            }
        }
    }
}
#endif

QWatch::QWatch(QWidget *parent)
    : QWidget(parent,WINDOWS_FLAGS_FRAMELESS)
{
    timeZoneDialog = NULL;
    calendarDialog = NULL;
    alarmClockDialog = NULL;
    alarmTimer = NULL;
    aboutDialog = NULL;
#ifdef Q_OS_WIN
    updateDialog = NULL;
#endif

    configuration = new Configuration(CONFIG_FOLDER);
    clockPainter = new ClockPainter(this);
    timeZones = new TimeZones();
    alarmAnimation = new AlarmAnimation(this);


    qtTranslator = new QTranslator(this);
    appTranslator = new QTranslator(this);
    QString lang = configuration->getString(CONFIG_LANGUAGE,"");

    if(lang.length() == 0) {
        lang = QLocale::system().name();
        configuration->setString(CONFIG_LANGUAGE,lang);
    }
    appTranslator->load("qwatch_" + lang,":/translations");
    qtTranslator->load("qt_" + lang, QLibraryInfo::location(QLibraryInfo::TranslationsPath));


    qApp->installTranslator(qtTranslator);
    qApp->installTranslator(appTranslator);

    setWindowTitle(STR_APPTITLE);
    QAction clockSize(this);
    clockSize.setData(configuration->getInt(CONFIG_CLOCKSIZE,2));
    setClockSize(&clockSize);

    QRect screen = QApplication::desktop()->geometry();
    move(screen.center() - rect().center());

    updateSecondClockTimeDifference();

    setAttribute(Qt::WA_TranslucentBackground);
    initPopupMenu();

    QTimer *timerWindow = new QTimer(this);
    connect(timerWindow, SIGNAL(timeout()), this, SLOT(update()));
    timerWindow->start(1000);

    QTimer *timerTrayIcon = new QTimer(this);
    connect(timerTrayIcon, SIGNAL(timeout()), this, SLOT(updateTrayIcon()));
    timerTrayIcon->start(60*1000);

#ifdef Q_OS_WIN
    QTimer *timerMonthlyUpgradeCheck = new QTimer(this);
    connect(timerMonthlyUpgradeCheck, SIGNAL(timeout()), this, SLOT(performMonthlyUpgrade()));
    //every 90 minutes, check if we should check for new upgrade
    timerMonthlyUpgradeCheck->start(90*60*1000);
#endif

    QTimer *timerFramelessMode = new QTimer(this);
    connect(timerFramelessMode, SIGNAL(timeout()), this, SLOT(checkFramelessMode()));
    timerFramelessMode->start(2000);

    timerSecondClockSynchronisation = new QTimer(this);
    connect(timerSecondClockSynchronisation, SIGNAL(timeout()), this, SLOT(updateSecondClockTimeDifferenceTimer()));
    //trigger the timer at next-hour:00:05 and then each 30 minutes
    QTime currentTime = QTime::currentTime();
    int secondsLeftToNextHour = 60*60 - (currentTime.minute()*60 + currentTime.second());
    timerSecondClockSynchronisation->start(secondsLeftToNextHour+5);

    checkFramelessMode();
    alarmTimeChanged(QTime::currentTime(), true);
    initTray();
    updateTrayIcon();
    #ifdef Q_OS_WIN
    deleteLocalSetupFiles();
    #endif
    double opacity = 1.0-configuration->getInt(CONFIG_TRANSPARENCY,10)/100.0;
    setWindowOpacity(opacity);
}

void QWatch::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton) {
        QPoint origin = pos();

        origin += event->pos() - mousePressPoint;
        move(origin);
    }

}

void QWatch::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton) {
        setCursor(Qt::SizeAllCursor);
        mousePressPoint = event->pos();
    } else
    if(event->buttons() & Qt::RightButton) {
        popupMenu->exec(QCursor::pos());
    }
}

void  QWatch::mouseReleaseEvent(QMouseEvent *)
{
    setCursor(Qt::ArrowCursor);
}

void QWatch::showClock() {
    show();
    showAction->setEnabled(false);
    hideAction->setEnabled(true);
}


void QWatch::initTray()
{
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(popupMenu);

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(showClock(QSystemTrayIcon::ActivationReason)));
}



void QWatch::updateSecondClockTimeDifference() {
    secondClockTimeDifferenceInSeconds = 0;
    QString timezone = configuration->getString(CONFIG_SECONDTIMEZONE,"");
    if(timezone.length()>0) {
        QDateTime localTime = QDateTime::currentDateTime();
        QDateTime secondTime = timeZones->getLocalTime(timezone);

        secondClockTimeDifferenceInSeconds = localTime.secsTo(secondTime);
    }
}

void QWatch::updateSecondClockTimeDifferenceTimer() {
    updateSecondClockTimeDifference();
    timerSecondClockSynchronisation->start(30*60*1000);
}

void QWatch::checkFramelessMode() {
    bool transparency = SystemInfo::canDrawTransparentWidgets();
    if(transparency == false) {
        framelessWindowAction->setEnabled(false);
        transparencyMenu->setEnabled(false);
        if(windowFlags() & Qt::FramelessWindowHint) {
            setAttribute(Qt::WA_TranslucentBackground,false);
            setAttribute(Qt::WA_NoSystemBackground,false);
            setWindowFlags(WINDOWS_FLAGS_FRAME);
            show();
        }
    } else {
        transparencyMenu->setEnabled(true);
        framelessWindowAction->setEnabled(true);
        if(framelessWindowAction->isChecked() && ((windowFlags() & Qt::FramelessWindowHint) == 0)) {
            setAttribute(Qt::WA_TranslucentBackground);
            setAttribute(Qt::WA_NoSystemBackground);
            setWindowFlags(WINDOWS_FLAGS_FRAMELESS);
            show();
        }
    }
}

void QWatch::updateTrayIcon()
{
    static QColor transparent(0,0,0,0);
    QPixmap tryIconPixmap(TRAYICON_PIXMAP_SIZE,TRAYICON_PIXMAP_SIZE);

    QTime time = QTime::currentTime();

    tryIconPixmap.fill(transparent);

    QPainter *painter = new QPainter(&tryIconPixmap);
    clockPainter->paintTrayIcon(this, painter, time, TRAYICON_PIXMAP_SIZE);
    QIcon icon(tryIconPixmap);

    trayIcon->setIcon(icon);
    setWindowIcon(icon);
    delete painter;
}

void QWatch::paintEvent(QPaintEvent *)
{
    QTime time = QTime::currentTime();

    QPainter *painter = new QPainter(this);

    clockPainter->paintClock(this, painter, time, this->clockSize, secondClockTimeDifferenceInSeconds);

    QString tooltip = QDateTime::currentDateTime().toString(Qt::DefaultLocaleLongDate);
    trayIcon->setToolTip(tooltip);
    setToolTip(tooltip);
    trayIcon->show();
    setWindowIconText(tooltip);

    delete painter;
}


 void QWatch::changeEvent(QEvent *event)
 {
     if (event->type() == QEvent::LanguageChange) {
         retranslateUi();
     } else {
         QWidget::changeEvent(event);
     }
 }
