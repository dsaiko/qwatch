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
 * Class handling XML configuration
 */

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QtGui>
#include <QString>
#include <QtXml>
#include <QMap>


static const QString configFileName = "config.xml";

class Configuration {
    public:
        Configuration(QString folder);
        ~Configuration();
        int getInt(QString key, int defaultValue);
        QString getString(QString key, QString defaultValue);
        void setInt(QString key, int value);
        void setString(QString key, QString value);
        QString getConfigFolderName() { return configFolderName; }
        static QString getSettingsFolder();
    protected:
        QString configFolderName;
        QString settingsFolder;
        bool load();
        bool save();

    private:
        QMap<QString, QString> map;
};

#endif // CONFIGURATION_H
