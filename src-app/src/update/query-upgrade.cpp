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
#include "update/query-upgrade.h"
#include "version.h"
#include <QString>
#include <QDebug>
#include <QStringList>


QueryUpgrade::QueryUpgrade(QString lang)
{
    this->lang = lang;
    if(this->lang.contains("_")) {
        this->lang = this->lang.split("_").first();
    }
    connect(this,SIGNAL(finished()),this,SLOT(deleteLater()));
}

QueryUpgrade::~QueryUpgrade()
{
}

void QueryUpgrade::run()
{
    bool ok = true;
    UpdateInfo *updateInfo = new UpdateInfo();

    Inet internet;
    QString downloadSite = "https://qwatch.googlecode.com/files/";
    QString currentVersionFileName = downloadSite+QString(STR_APPTITLE).toLower()+"-currentversion.xml";
    HINTERNET connection = internet.openUrl(currentVersionFileName);
    if(!connection) {
        qDebug() << "Can not open internet connection for  "<<currentVersionFileName;
        emit queryFinished(false, updateInfo);
        return;
    }

    long fileSize = internet.getFileSize(connection);
    if(fileSize > 1024) {
        qDebug() << "Can not download currentversion.xml - file size too big:" << fileSize;
        internet.closeUrl(connection);
        emit queryFinished(false, updateInfo);
        return;
    }

    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    ok = internet.downloadFile(connection, &buffer, false);
    internet.closeUrl(connection);

    if(!ok) {
        qDebug() << "Can not download currentversion.xml.";
        emit queryFinished(false, updateInfo);
        return;
    }
    if(fileSize > 0) {
        if(buffer.size() != fileSize) {
            qDebug() << "Can not download currentversion.xml - file size does not match.";
            emit queryFinished(false, updateInfo);
            return;
        }
    }
    if(buffer.size() < 100) {
        qDebug() << "Can not download currentversion.xml - file size too small.";
        emit queryFinished(false, updateInfo);
        return;
    }


    buffer.seek(0);
    QXmlStreamReader xmlReader(&buffer);

    while(!xmlReader.atEnd()) {
        xmlReader.readNext();
        if(xmlReader.isStartElement()) {
            QString name=xmlReader.name().toString();
            if(name == "number") {
                QString value = xmlReader.readElementText();
                updateInfo->availableVersion = value;
            }
            if(name == "date") {
                QString value = xmlReader.readElementText();
                updateInfo->releaseDate = QDate::fromString(value, "yyyy-MM-dd");
            }
            if(name == "file") {
                QString value = xmlReader.readElementText();
                updateInfo->downloadFile = value;
            }
            if(name == "size") {
                QString value = xmlReader.readElementText();
                updateInfo->fileSize = value.toLong(&ok);
                if(!ok) {
                    qDebug() << "Can not read currentversion.xml - invalid file size.";
                    emit queryFinished(false, updateInfo);
                    return;
                }
            }
            if(name == "hash") {
                QString value = xmlReader.readElementText();
                updateInfo->fileMD5 = value;
            }
        }
    }

    connection = internet.openUrl(updateInfo->downloadFile);
    if(!connection) {
        qDebug() << "Can not open internet connection for" << updateInfo->downloadFile;
        emit queryFinished(false, updateInfo);
        return;
    }

    //validate existence of download file and it's size
    fileSize = internet.getFileSize(connection);
    internet.closeUrl(connection);
    if(fileSize >=0 && fileSize < 1024) {
        qDebug() << "Can not download update file - file size too small:" << fileSize;
        emit queryFinished(false, updateInfo);
        return;
    }
    if(fileSize >0 && fileSize != updateInfo->fileSize) {
        qDebug() << "Can not download update file - file size conflict:" << fileSize << "x" << updateInfo->fileSize;
        emit queryFinished(false, updateInfo);
        return;
    }


    //get changelog
    QString currentLanguageChangeLogUrl = downloadSite+QString(STR_APPTITLE).toLower()+"-changelog-"+lang+".txt";
    QString globalChangeLogUrl = downloadSite+QString(STR_APPTITLE).toLower()+"-changelog.txt";
    connection = internet.openUrl(currentLanguageChangeLogUrl);
    if(!connection) {
        connection = internet.openUrl(globalChangeLogUrl);
    }
    if(!connection) {
        qDebug() << "Can not download changelog.";
        emit queryFinished(false, updateInfo);
        return;
    }
    QBuffer changelog;
    changelog.open(QBuffer::ReadWrite);
    if(!internet.downloadFile(connection, &changelog, false)) {
        internet.closeUrl(connection);
        qDebug() << "Can not download changelog(2).";
        emit queryFinished(false, updateInfo);
        return;
    }
    internet.closeUrl(connection);
    updateInfo->changelog=QString(changelog.buffer());

    //check if the remote version is new
    QStringList remoteVersion = updateInfo->availableVersion.split(".");
    QStringList currentVersion = getVersion().split(".");

    updateInfo->isNewVersion = false;
    if(remoteVersion.size()==3 && currentVersion.size()==3) {
        int r1 = remoteVersion[0].toInt();
        int r2 = remoteVersion[1].toInt();
        int r3 = remoteVersion[2].toInt();
        int c1 = currentVersion[0].toInt();
        int c2 = currentVersion[1].toInt();
        int c3 = currentVersion[2].toInt();

        if( (r1 > c1) || (r1 == c1 && r2 > c2) || (r1 == c1 && r2 == c2 && r3 > c3)) {
            updateInfo->isNewVersion = true;
        }
    }

    emit queryFinished(true, updateInfo);
}
