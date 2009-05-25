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
 *
 * QWatch - analog watch with extended functionality
 * under GPL Licence
 *
 * Definition of Time Zones provider
 */

#include "timezones.h"

QList<QString> * TimeZones::listTimeZones()
{
    QList<QString> *zones = new QList<QString>();
    QDir * zoneinfodir = new QDir("/usr/share/zoneinfo");
    if(!zoneinfodir->exists()) {
        zoneinfodir = new QDir("/usr/lib/zoneinfo");
    }
    if(!zoneinfodir->exists()) {
        return NULL;
    }

    foreach(QFileInfo info, zoneinfodir->entryInfoList()) {
        if(info.isDir()) {
            QString dirName = info.fileName();
            if(dirName == "right") continue;
            if(dirName == "posix") continue;
            if(dirName == "SystemV") continue;
            if(dirName.startsWith(".")) continue;

            foreach(QFileInfo info2, QDir(info.absoluteFilePath()).entryInfoList()) {
                if(info2.isFile()) {
                    zones->append(dirName+" / "+info2.fileName());
                }
            }
        }
    }
    delete zoneinfodir;
    return zones;
}

struct QDateTime TimeZones::getLocalTime(QString timezone)
{
  time_t rawtime;
  struct tm *tm;

  QString envTZ = "TZ=" + timezone;
  putenv(envTZ.toAscii().data());
  time(&rawtime);
  tm = localtime( &rawtime );
  putenv((char*)"TZ");

  QDateTime secondTime(QDate(tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday),QTime(tm->tm_hour, tm->tm_min, tm->tm_sec));
  return secondTime;
}
