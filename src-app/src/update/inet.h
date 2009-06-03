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
 * $Rev: 23 $
 *
 * QWatch - analog watch with extended functionality
 * under GPL Licence
 *
 * Auto updating functionality
 */

#ifndef INET_H
#define INET_H

#include "qt_windows.h"
#include "wininet.h"
#include <QList>
#include <QBuffer>

class Inet : public QObject
{
    Q_OBJECT

signals:
    void downloading(long size);
    void downloadFinished(bool ok);

public:
    Inet();
    ~Inet();

    bool isInternetAvailable();
    HINTERNET openUrl(QString URL);
    long getFileSize(HINTERNET hSession);
    bool downloadFile(HINTERNET hSession, QIODevice *data, bool emitSignals=true);
    void closeUrl(HINTERNET hSession);

protected:
    HINTERNET hInternet;
    bool internetAvailable;

};

#endif // INET_H
