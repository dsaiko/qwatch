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
 * Class handling XML configuration
 */

#include "config/configuration.h"

#ifdef Q_OS_WIN
#include <qt_windows.h>
#include "shlobj.h"
#endif

Configuration::Configuration(QString folder) {
    this->configFolderName = folder;
    settingsFolder = getSettingsFolder();
    load();
}

Configuration::~Configuration() {
}


int Configuration::getInt(QString key, int defaultValue) {
    if(map.contains(key)) {
        QString value = map.value(key);
        bool ok;

        int intValue = value.toInt(&ok);
        if(ok == true) {
            return intValue;
        }
    }
    return defaultValue;
}

QString Configuration::getString(QString key, QString defaultValue) {
    if(map.contains(key)) {
        return map.value(key);
    }
    return defaultValue;
}

void Configuration::setInt(QString key, int value) {
    setString(key, QString::number(value));
}

void Configuration::setString(QString key, QString value) {
    map[key] = value;
    save();
}


QString Configuration::getSettingsFolder() {
#ifdef Q_OS_LINUX
    QString settingsFolder;
    settingsFolder = QDir::homePath();
    return settingsFolder;
#endif

#ifdef Q_OS_WIN
     QString settingsFolder;
     TCHAR szPath[MAX_PATH];
     LPITEMIDLIST pidlRoot = NULL;
     HRESULT hResult=SHGetFolderLocation(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, &pidlRoot);
     if(hResult == S_OK && pidlRoot)
     {
        SHGetPathFromIDList(pidlRoot, szPath);
        settingsFolder = QString::fromStdWString(szPath);
     } else {
        settingsFolder = QDir::homePath();
     }
     if(pidlRoot) {
         ILFree(pidlRoot);
     }
     return settingsFolder;
#endif
}

bool Configuration::load() {


    QDir configFolder(settingsFolder + QDir::separator() + configFolderName);
    QFile configFile(configFolder.absolutePath() + QDir::separator() + configFileName);
    if(!configFile.exists()) return true;

    if(!configFile.open(QFile::ReadOnly | QFile::Text)) {
        return false;
    }

    QXmlStreamReader xmlReader(&configFile);

    xmlReader.readNext();

    while(!xmlReader.atEnd()) {
        if(xmlReader.isStartElement() && xmlReader.name() == "config") {            

            QString key = xmlReader.attributes().value("key").toString();
            QString value = xmlReader.readElementText();

            map[key] = value;
        } else {
            xmlReader.readNext();
        }
    }

    configFile.close();
    if(configFile.error()) {
        return false;
    }
    return true;
}

bool Configuration::save() {
    QList<QString> keys = map.keys();
    QDir configFolder(settingsFolder + QDir::separator() + configFolderName);
    configFolder.mkdir(configFolder.absolutePath());
    QFile configFile(configFolder.absolutePath() + QDir::separator() + configFileName);

    if(!configFile.open(QFile::WriteOnly | QFile::Text)) {
        return false;
    }

    QXmlStreamWriter xmlWriter(&configFile);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("configuration");

    foreach(QString key, keys) {
        QString value = map.value(key);
        xmlWriter.writeStartElement("config");
        xmlWriter.writeAttribute("key",key);
        xmlWriter.writeCharacters(value);
        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndDocument();
    configFile.close();
    if(configFile.error()) {
        return false;
    }
    return true;
}
