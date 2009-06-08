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
 * About dialog
 */

#include "menu/update.h"
#include "version.h"
#include "config/constants-config.h"
#include "qwatch.h"
#include "update/query-upgrade.h"
#include "update/download-upgrade.h"
#include <QMessageBox>
#include <QLocale>
#include <qt_windows.h>
#include <shellapi.h>


UpdateDialog::UpdateDialog(QWatch *parent)
    : QDialog(parent), ui(new Ui::UpdateDialogClass)
{
    ui->setupUi(this);
    this->qwatch = parent;
    updateInfo = NULL;

    ui->editInstalledVersion->setText(getVersion());
    QDate versionDate = getVersionDate();
    QString date=versionDate.toString(Qt::DefaultLocaleShortDate);
    QString fullYear=versionDate.toString("yyyy");
    QString shortYear=versionDate.toString("yy");
    if(date.contains(fullYear) == false) {
        date = date.replace(shortYear,fullYear);
    }
    ui->editReleaseDate->setText(date);
    ui->editApplicationName->setText(STR_APPTITLE);

    ui->btnDownload->setEnabled(false);
    ui->btnInstall->setEnabled(false);
    ui->progressBar->setEnabled(false);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(1);
    ui->progressBar->setValue(0);

    this->updateInfo = NULL;
}


void UpdateDialog::init()
{
    int answer = QMessageBox::question(this, tr("Application upgrade ..."),
                                       tr("Query automatically new application version ?"),
                                       QMessageBox::Yes | QMessageBox::No,
                                       QMessageBox::Yes);
    if(answer == QMessageBox::Yes) {
        on_btnQuery_clicked();
    }
}

UpdateDialog::~UpdateDialog()
{
    delete ui;
    if(updateInfo)
        delete updateInfo;
}

void UpdateDialog::on_btnClose_clicked()
{
    hide();
}

void UpdateDialog::on_btnQuery_clicked()
{
    QueryUpgrade *query = new QueryUpgrade(qwatch->configuration->getString(CONFIG_LANGUAGE,""));
    connect(query, SIGNAL(queryFinished(bool,UpdateInfo*)), this, SLOT(queryFinished(bool,UpdateInfo*)));

    ui->btnQuery->setEnabled(false);
    ui->btnDownload->setEnabled(false);
    ui->btnInstall->setEnabled(false);
    query->start();
}

void UpdateDialog::queryFinished(bool ok, UpdateInfo * updateInfo)
{
    if(!isVisible()) return;
    QString queryStatusTitle = tr("Query Upgrade Status");
    QString newVersionAvailable = tr("New version is available! You can proceed by downloading the application installer.");
    QString noNewVersion = tr("Your application is up to date. Thank you for your interest.");

    if(this->updateInfo) {
        delete this->updateInfo;
    }
    this->updateInfo = updateInfo;

    if(ok) {       
        ui->editAvailableVersion->setText(updateInfo->availableVersion);
        QDate versionDate = updateInfo->releaseDate;
        QString date=versionDate.toString(Qt::DefaultLocaleShortDate);
        QString fullYear=versionDate.toString("yyyy");
        QString shortYear=versionDate.toString("yy");
        if(date.contains(fullYear) == false) {
            date = date.replace(shortYear,fullYear);
        }
        ui->editAvailableReleaseDate->setText(date);
        ui->editDownloadFile->setText(updateInfo->downloadFile);
        ui->editFileMD5->setText(updateInfo->fileMD5);
        QLocale locale;
        ui->editFileSize->setText(locale.toString((int)updateInfo->fileSize/1024)+" kB");

        if(updateInfo->isNewVersion) {
            ui->editChangelog->setText(newVersionAvailable+"\n\n"+updateInfo->changelog);
        } else {
            ui->editChangelog->setText(noNewVersion+"\n\n"+updateInfo->changelog);
            ok=false;
            QMessageBox::information(this, queryStatusTitle,
                                     noNewVersion,
                                     QMessageBox::Close,
                                     QMessageBox::Close);
        }
    } else {
        QMessageBox::critical(this, tr("Query Upgrade Error"),
                              tr("Error while quering application upgrade info."),
                              QMessageBox::Close,
                              QMessageBox::Close);
    }

    if(ok) {
        ui->btnQuery->setEnabled(true);
        ui->btnDownload->setEnabled(true);
        ui->btnInstall->setEnabled(false);
        ui->progressBar->setEnabled(false);
        ui->progressBar->setMinimum(0);
        ui->progressBar->setMaximum(1);
        ui->progressBar->setValue(0);
        ui->btnDownload->setFocus();

        int answer = QMessageBox::question(this, tr("Application upgrade ..."),
                                           tr("New version available.\nDownload automatically new application version ?"),
                                           QMessageBox::Yes | QMessageBox::No,
                                           QMessageBox::Yes);
        if(answer == QMessageBox::Yes) {
            on_btnDownload_clicked();
        }
    } else {
        ui->btnQuery->setEnabled(true);
        ui->btnDownload->setEnabled(false);
        ui->btnInstall->setEnabled(false);
        ui->progressBar->setEnabled(false);
        ui->progressBar->setMinimum(0);
        ui->progressBar->setMaximum(1);
        ui->progressBar->setValue(0);
    }
}

void UpdateDialog::on_btnDownload_clicked()
{
    DownloadUpgrade *download = new DownloadUpgrade(ui->progressBar, this->updateInfo);
    connect(download, SIGNAL(downloadFinished(bool,UpdateInfo*)), this, SLOT(downloadFinished(bool,UpdateInfo*)));

    ui->btnQuery->setEnabled(false);
    ui->btnDownload->setEnabled(false);
    ui->btnInstall->setEnabled(false);
    ui->progressBar->setEnabled(true);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(updateInfo->fileSize);
    ui->progressBar->setValue(0);

    download->start();
}

void UpdateDialog::downloadFinished(bool ok, UpdateInfo * updateInfo)
{
    if(!isVisible()) return;
    if(!ok) {
        QMessageBox::critical(this, tr("Query Upgrade Error"),
                              tr("Error while downloading application upgrade."),
                              QMessageBox::Close,
                              QMessageBox::Close);
    }

    if(ok) {
        ui->btnQuery->setEnabled(true);
        ui->btnDownload->setEnabled(true);
        ui->btnInstall->setEnabled(true);
        ui->btnInstall->setFocus();

        int answer = QMessageBox::question(this, tr("Application upgrade ..."),
                                           tr("New application version downloaded sucesfully.\nStart upgrade now ?"),
                                           QMessageBox::Yes | QMessageBox::No,
                                           QMessageBox::Yes);
        if(answer == QMessageBox::Yes) {
            on_btnInstall_clicked();
        }

    } else {
        ui->btnQuery->setEnabled(true);
        ui->btnDownload->setEnabled(true);
    }
}

void UpdateDialog::on_btnInstall_clicked()
{
    hide();
    qwatch->hide();
    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    ShellExecuteW(NULL, NULL, (WCHAR*)updateInfo->localFilePath.utf16(), NULL, NULL, SW_SHOWNORMAL);
    qApp->quit();
}

