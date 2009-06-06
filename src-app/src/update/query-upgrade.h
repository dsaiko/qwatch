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
 * $Rev: 38 $
 * $Id: inet.h 38 2009-06-04 08:07:10Z dusan.saiko $
 *
 * QWatch - analog watch with extended functionality
 * under GPL Licence
 *
 * Auto updating functionality
 */

#ifndef QUERY_UPGRADE_H
#define QUERY_UPGRADE_H

#include "qt_windows.h"
#include "wininet.h"
#include <QThread>
#include <QList>
#include <QBuffer>
#include "menu/update.h"


class QueryUpgrade : public QThread
{
    Q_OBJECT

signals:
    void queryFinished(bool okflag, UpdateInfo &updateInfo);

public:
    QueryUpgrade();
    ~QueryUpgrade();
    void run();
};

#endif // QUERY_UPGRADE_H