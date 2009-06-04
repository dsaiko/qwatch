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
 * $Id$
 *
 * QWatch - analog watch with extended functionality
 * under GPL Licence
 *
 * Auto updating functionality
 */

#include "update/inet.h"
#include <QString>


Inet::Inet()
{
    hInternet = InternetOpenA("AutoUpdateAgent", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);

    internetAvailable = true;
    DWORD dwType;
    if (hInternet == NULL || (!InternetGetConnectedState(&dwType, 0))) {
        internetAvailable = false;
    }
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

    DWORD options = INTERNET_FLAG_HYPERLINK|INTERNET_FLAG_RESYNCHRONIZE|INTERNET_FLAG_RELOAD;
    HINTERNET hSession = InternetOpenUrl(hInternet, canonicalURL, NULL, 0, options, 0);

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
    if(!hSession) return 0;
    if(!internetAvailable) return 0;

    char sizeBuffer[64];
    DWORD sizeBufferLength = 64;

    bool bRet = HttpQueryInfo(hSession, HTTP_QUERY_CONTENT_LENGTH, sizeBuffer, &sizeBufferLength, NULL);
    if(bRet) {
        return QString::fromStdWString((TCHAR*)sizeBuffer).toLong();
    }
    return 0;
}


bool Inet::downloadFile(HINTERNET hSession, QIODevice *data, bool emitSignals)
{
        if(!hSession) return false;
        if(!internetAvailable) return false;

        static const int TRANSFER_SIZE=4096;

        BYTE	buffer[TRANSFER_SIZE];
        DWORD	size, totalSize = 0;
        BOOL ok;

        while(true) {
                ok = InternetReadFile(hSession, buffer, TRANSFER_SIZE, &size);

                if (ok && size > 0) {
                        totalSize += size;
                        if(emitSignals) {
                            emit downloading(totalSize);
                        }
                        data->write((char *)buffer, size);
                }
                else {
                    break;
                }
        }

        if(emitSignals) {
            emit downloadFinished(ok);
        }

        return ok;
}
