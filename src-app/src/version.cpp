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
 * Version file
 */

#include "version.h"
#include <QRegExp>
#include <QDate>
#include <QDebug>
#include <QString>
#include <QStringList>

QString getVersion()
{
    static QString major = MAJORVERSION;
    static QString minor = MINORVERSION;

    return major + minor.replace(QRegExp("[^\\d]"),"");
}

QDate getVersionDate()
{
    //Date: 2009-06-03 18:41:15 +1000 (st, 03 VI 2009)
    static QString date = VERSIONDATE;

    QString d = date.replace(QRegExp("[^\\d- ]"),"").trimmed();
    d=d.split(" ").first();

    QDate versionDate = QDate::fromString(d,"yyyy-MM-dd");
    return versionDate;
}
