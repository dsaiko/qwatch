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

#include "update/inet.h"
#include "qwatch.h"
#include "update/download-upgrade.h"
#include "version.h"
#include <QString>
#include <QDebug>
#include <QStringList>
#include <QDir>
#include <QFile>
#include "config/configuration.h"
#include "config/constants-config.h"


DownloadUpgrade::DownloadUpgrade(QProgressBar *progressBar, UpdateInfo *updateInfo)
{
    connect(this,SIGNAL(finished()),this,SLOT(deleteLater()));
    this->updateInfo = updateInfo;
    this->progressBar = progressBar;
}

DownloadUpgrade::~DownloadUpgrade()
{
}

void DownloadUpgrade::run()
{
    QDir configFolder(Configuration::getSettingsFolder() + QDir::separator() + CONFIG_FOLDER);
    configFolder.mkdir(configFolder.absolutePath());
    QString setupFileName="?";
    QFile setupFile(configFolder.absolutePath() + QDir::separator() + updateInfo->downloadFile.split("/").last());
    updateInfo->localFilePath = setupFile.fileName();

    if(setupFile.exists()) {
        if(!setupFile.remove()) {
            qDebug() << "Can not delete old setup file";
            emit downloadFinished(false, this->updateInfo);
            return;
        }
    }

    if(!setupFile.open(QFile::WriteOnly)) {
        qDebug() << "Can not delete old setup file";
        emit downloadFinished(false, this->updateInfo);
        return;
    }

    Inet internet;
    HINTERNET connection = internet.openUrl(updateInfo->downloadFile);
    if(!connection) {
        qDebug() << "Can not open remote setup file";
        emit downloadFinished(false, this->updateInfo);
        return;
    }

    connect( &internet, SIGNAL(downloading(int)),progressBar,SLOT(setValue(int)));

    if(!internet.downloadFile(connection, &setupFile, true)) {
        qDebug() << "Can not download remote setup file";
        internet.closeUrl(connection);
        emit downloadFinished(false, this->updateInfo);
        return;
    }
    internet.closeUrl(connection);
    setupFile.close();

    if(setupFile.size() != updateInfo->fileSize) {
        qDebug() << "Setup file size conflict:"<<setupFile.size() << "x" << updateInfo->fileSize;
        setupFile.remove();
        emit downloadFinished(false, this->updateInfo);
        return;
    }

    if(internet.getDownloadMD5() != updateInfo->fileMD5) {
        qDebug() << "Setup file size checksum conflict:"<<updateInfo->fileMD5 << "x" << internet.getDownloadMD5();
        setupFile.remove();
        emit downloadFinished(false, this->updateInfo);
        return;
    }

    emit downloadFinished(true, this->updateInfo);
}
