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
 * Auto updating functionality
 */

#ifndef DOWNLOAD_UPGRADE_H
#define DOWNLOAD_UPGRADE_H

#include "qt_windows.h"
#include "wininet.h"
#include <QThread>
#include <QList>
#include <QBuffer>
#include <QProgressBar>
#include "menu/update.h"


class DownloadUpgrade : public QThread
{
    Q_OBJECT

public:
    DownloadUpgrade(QProgressBar *progressBar, UpdateInfo *updateInfo);
    ~DownloadUpgrade();
    void run();

signals:
    void downloadFinished(bool okflag, UpdateInfo *updateInfo);

protected:
    UpdateInfo *updateInfo;
    QProgressBar *progressBar;
};

#endif // DOWNLOAD_UPGRADE_H
