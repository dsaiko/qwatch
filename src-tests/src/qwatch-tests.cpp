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
 * $Rev: 45 $
 *
 * QWatch - analog watch with extended functionality
 * under GPL Licence
 *
 * Unit tests
 */

#include "inc/qwatch-tests.h"
#include "config/configuration.h"
#include "qwatch.h"
#include "sound/sound.h"
#include "version.h"

void QWatchTests::testConfiguration()
{
    Configuration config(".tmp");

    QCOMPARE(config.getInt("TEST-INT",15),15);
    config.setInt("TEST-INT",16);
    QCOMPARE(config.getInt("TEST-INT",15),16);

    QCOMPARE(config.getString("TEST-STRING","1"),QString("1"));
    config.setString("TEST-STRING","16");
    QCOMPARE(config.getString("TEST-INT","1"),QString("16"));


    QDir configFolder(QDir::homePath() + QDir::separator() + config.getConfigFolderName());
    QFile configFile(QDir::homePath() + QDir::separator() + config.getConfigFolderName() + QDir::separator() + "config.xml");

    QVERIFY(configFile.exists());
    QVERIFY(configFile.exists());
    QVERIFY(configFile.size() > 100);

    configFile.remove();
    configFolder.rmdir(configFolder.absolutePath());
}


void QWatchTests::testGui()
{
    QWatch qwatch(NULL);
    qwatch.displaySecondTimeZoneDialog();
    QVERIFY(qwatch.timeZoneDialog != NULL);
    qwatch.displayCalendar();
    QVERIFY(qwatch.calendarDialog != NULL);
    qwatch.displayAlarmClockDialog();
    QVERIFY(qwatch.alarmClockDialog != NULL);

    QBENCHMARK {
        qwatch.update();
    }

}

void QWatchTests::testSound()
{
    WavSound::playWav(":/alarm.wav");
    QTest::qWait(3000);
}


void QWatchTests::testVersion() {
    QString version = getVersion();

    QVERIFY(version.size() > 1);
    QCOMPARE(version,version.replace(QRegExp("[^\\d\\.]"),""));
}

QTEST_MAIN(QWatchTests)

