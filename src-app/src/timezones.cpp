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
 *
 * QWatch - analog watch with extended functionality
 * under GPL Licence
 *
 * Definition of Time Zones provider
 */

#include "timezones.h"
#include <QDebug>
#include <QDir>

#ifdef Q_OS_LINUX

TimeZones::TimeZones() {
}

TimeZones::~TimeZones() {
}

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

QDateTime TimeZones::getLocalTime(QString timezone)
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
#endif


#ifdef Q_OS_WIN

#define MAX_KEY_LENGTH 512

QString getStringRegistryKeyValue(HKEY hKey, QString valueName) {
    DWORD dataSize = MAX_KEY_LENGTH;
    BYTE  value[MAX_KEY_LENGTH];
    DWORD valueType;
    DWORD retCode;

    retCode = RegQueryValueEx(hKey, (const WCHAR*) valueName.utf16(), NULL, &valueType, value, &dataSize);
    if(retCode == ERROR_SUCCESS && valueType == REG_SZ) {
       QString s = QString::fromUtf16((const ushort*)value,dataSize/sizeof(WCHAR)-1);
       return s;
    }

    return "";
}

TZIREG* getTZIRegistryKeyValue(HKEY hKey, QString valueName) {
    DWORD dataSize = MAX_KEY_LENGTH;
    BYTE  value[MAX_KEY_LENGTH];
    DWORD valueType;
    DWORD retCode;

    retCode = RegQueryValueEx(hKey, (const WCHAR*) valueName.utf16(), NULL, &valueType, value, &dataSize);

    if(retCode == ERROR_SUCCESS && valueType == REG_BINARY) {
        TZIREG *tzi = new TZIREG;
        memcpy((BYTE*)tzi, value, dataSize);
        return tzi;
    }
    return NULL;
}

TimeZone* processTimeZone(QString keyName) {
    HKEY hKey;

    DWORD retCode = RegOpenKeyEx(HKEY_LOCAL_MACHINE, (const WCHAR*)keyName.utf16(), 0, KEY_READ, &hKey);
    if(retCode != ERROR_SUCCESS) return NULL;

    QString display = getStringRegistryKeyValue(hKey,"Display");
    QString dlt = getStringRegistryKeyValue(hKey,"Dlt");
    QString std = getStringRegistryKeyValue(hKey,"Std");
    TZIREG* tziReg = getTZIRegistryKeyValue(hKey, "TZI");

    RegCloseKey(hKey);


    TIME_ZONE_INFORMATION *tzi = new TIME_ZONE_INFORMATION();
    ZeroMemory(tzi, sizeof(*tzi));

    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, std.toLatin1().constData(), -1, tzi->StandardName, 32);
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, dlt.toLatin1().constData(), -1, tzi->DaylightName , 32);

    tzi->Bias = tziReg->bias;
    tzi->StandardDate=tziReg->standardDate;
    tzi->StandardBias=tziReg->standardBias;
    tzi->DaylightDate=tziReg->daylightDate;
    tzi->DaylightBias=tziReg->daylightBias;

    TimeZone *t = new TimeZone();
    t->displayName = display;
    t->timeZoneInformation=tzi;

    return t;
}


 bool caseTimeZoneLessThan(const TimeZone *t1, const TimeZone *t2)
 {
     QString d1 = t1->displayName;
     QString d2 = t2->displayName;
     return d1<d2;
 }

QList<TimeZone*> * enumerateTimeZones()
{
    TCHAR    keyName[MAX_KEY_LENGTH];
    DWORD    keyNameSize;
    HKEY     hKey;


    QList<TimeZone*> *result = new QList<TimeZone*>();

    //1.Open the registry key "Software\Microsoft\Windows NT\CurrentVersion\Time Zones"
    QString rootKeyName("Software\\Microsoft\\Windows NT\\CurrentVersion\\Time Zones");
    DWORD retCode = RegOpenKeyEx(HKEY_LOCAL_MACHINE, (const WCHAR*)rootKeyName.utf16(), 0, KEY_READ, &hKey);
    if(retCode != ERROR_SUCCESS) return false;


    DWORD i;

    retCode = ERROR_SUCCESS;

    for (i=0; retCode == ERROR_SUCCESS; i++)
    {
        keyNameSize = MAX_KEY_LENGTH;
        retCode = RegEnumKeyEx(hKey, i, keyName, &keyNameSize, NULL, NULL, NULL, NULL);
        if (retCode == ERROR_SUCCESS)
        {
            TimeZone *t=processTimeZone(rootKeyName+"\\"+QString::fromUtf16((const ushort*)keyName,keyNameSize));
            if(t!=NULL) {
                result->append(t);
            }
        }
    }

    RegCloseKey(hKey);

    qSort(result->begin(), result->end(), caseTimeZoneLessThan);
    return result;
}

TimeZones::TimeZones() {
    timeZoneList=enumerateTimeZones();
}

TimeZones::~TimeZones() {
    foreach(TimeZone *t, *timeZoneList) {
        delete t->timeZoneInformation;
        delete t;
    }
    delete timeZoneList;
}

QList<QString> * TimeZones::listTimeZones()
{

    QList<QString> *timeZoneNames = new QList<QString>;
    foreach(TimeZone *t, *timeZoneList) {
        timeZoneNames->append(t->displayName);
    }

    return timeZoneNames;
}

QDateTime TimeZones::getLocalTime(QString timezone)
{
    SYSTEMTIME systemTime;
    GetSystemTime(&systemTime);

    foreach(TimeZone *t, *timeZoneList) {
        QString currentLocalZoneName = t->displayName;
        currentLocalZoneName.replace('_',' ');
        currentLocalZoneName.replace(" ","");
        if(currentLocalZoneName == timezone) {

            SYSTEMTIME localTime;
            SystemTimeToTzSpecificLocalTime(t->timeZoneInformation, &systemTime, &localTime);

            QDate _localDate(localTime.wYear,localTime.wMonth,localTime.wDay);
            QTime _localTime(localTime.wHour,localTime.wMinute,localTime.wSecond,localTime.wMilliseconds);
            QDateTime localDateTime(_localDate, _localTime);

            return localDateTime;
        }
    }

    qDebug() << "Can not get local time for timezone" << timezone << "!";
    return QDateTime::currentDateTime();
}

#endif
