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
 * Update dialog
 */

#ifndef UPDATEDLG_H
#define UPDATEDLG_H


#include <QtGui/QDialog>
#include "config/configuration.h"

#include "ui_update.h"

class QWatch;

struct UpdateInfo {
    QString availableVersion;
    QDate releaseDate;
    QString downloadFile;
    long fileSize;
    QString fileMD5;
    QString changelog;
    QString localFilePath;
    bool    isNewVersion;
};

namespace Ui
{
    class UpdateDialogClass;
}

class UpdateDialog : public QDialog
{
    Q_OBJECT

public:
    UpdateDialog(QWatch *parent);
    ~UpdateDialog();
    Ui::UpdateDialogClass *ui;
    void init();
protected:
    QWatch *qwatch;

    UpdateInfo *updateInfo;
private slots:
    void on_btnInstall_clicked();
    void on_btnDownload_clicked();
    void on_btnQuery_clicked();
    void on_btnClose_clicked();
    void queryFinished(bool,UpdateInfo *);
    void downloadFinished(bool,UpdateInfo *);
};

#endif // UPDATEDLG_H
