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
#include <QString>
#include <QDebug>


Inet::Inet()
{
    hInternet = InternetOpenA("AutoUpdateAgent", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);

    internetAvailable = true;
    if (hInternet == NULL) {
        internetAvailable = false;
    }
}

bool Inet::isInternetConnected() {
    DWORD dwType;
    return InternetGetConnectedState(&dwType, 0);
}



Inet::~Inet()
{
    if (hInternet) {
        InternetCloseHandle(hInternet);
    }
}

HINTERNET Inet::openUrl(QString URL)
{
    if(!hInternet) return 0;
    if(!internetAvailable) return 0;

    // Canonicalization of the URL converts unsafe characters into escape character equivalents
    TCHAR canonicalURL[1024];
    DWORD nSize = 1024;
    InternetCanonicalizeUrl((WCHAR*)URL.utf16(), canonicalURL, &nSize, ICU_BROWSER_MODE);

    DWORD options = INTERNET_FLAG_HYPERLINK|INTERNET_FLAG_RESYNCHRONIZE|INTERNET_FLAG_RELOAD|INTERNET_FLAG_NO_COOKIES;
    HINTERNET hSession = InternetOpenUrl(hInternet, canonicalURL, NULL, 0, options, 0);

    char sizeBuffer[64];
    DWORD sizeBufferLength = 64;
    bool bRet = HttpQueryInfo(hSession, HTTP_QUERY_STATUS_CODE, sizeBuffer, &sizeBufferLength, NULL);
    if(bRet) {
        int responseCode = QString::fromStdWString((TCHAR*)sizeBuffer).toInt();
        if(responseCode != 200) {
            bRet = false;
            qDebug() << "Can not open URL - response code" << responseCode << URL;
        }
    }
    if(bRet == false) {
        InternetCloseHandle(hSession);
        return NULL;
    }

    return hSession;
}

void Inet::closeUrl(HINTERNET hSession)
{
    if(hSession) {
        InternetCloseHandle(hSession);
    }
}

bool Inet::isInternetAvailable()
{
    return internetAvailable;
}

long Inet::getFileSize(HINTERNET hSession)
{
    if(!hSession) return -1;
    if(!internetAvailable) return -1;

    char sizeBuffer[64];
    DWORD sizeBufferLength = 64;

    bool bRet = HttpQueryInfo(hSession, HTTP_QUERY_CONTENT_LENGTH, sizeBuffer, &sizeBufferLength, NULL);
    if(bRet) {
        return QString::fromStdWString((TCHAR*)sizeBuffer).toLong();
    }
    return -1;
}


bool Inet::downloadFile(HINTERNET hSession, QIODevice *data, bool emitSignals)
{
        if(!hSession) return false;
        if(!internetAvailable) return false;

        MD5_CTX md5ctx;
        MD5 md5;
        md5.MD5Init(&md5ctx);

        static const int TRANSFER_SIZE=4096;

        BYTE	buffer[TRANSFER_SIZE];
        DWORD	size, totalSize = 0;
        BOOL ok;

        while(true) {
                ok = InternetReadFile(hSession, buffer, TRANSFER_SIZE, &size);

                if (ok && size > 0) {
                        totalSize += size;
                        if(emitSignals) {
                            emit downloading((int)totalSize);
                        }
                        data->write((char *)buffer, size);
                        md5.MD5Update(&md5ctx, (unsigned char *)buffer, size);
                }
                else {
                    break;
                }
        }

        unsigned char digest[16];
        md5.MD5Final(digest, &md5ctx);


        QString md5Hash="";
        for(int i=0; i<16; i++)
        {
            QString n = QString::number(digest[i],16);
            if(n.length() < 2) {
                n = "0" + n;
            }
            md5Hash += n;
        }
        downloadMD5 = md5Hash;

        if(emitSignals) {
            emit downloadFinished(ok);
        }

        return ok;
}


QString Inet::getDownloadMD5() {
    return downloadMD5;
}
