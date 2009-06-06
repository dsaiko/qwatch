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


UpdateDialog::UpdateDialog(QWatch *parent)
    : QDialog(parent), ui(new Ui::UpdateDialogClass)
{
    ui->setupUi(this);
    this->qwatch = parent;
    updateInfo = NULL;
    localPath = NULL;

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

}


void UpdateDialog::init()
{
}

UpdateDialog::~UpdateDialog()
{
    delete ui;
    if(localPath)
        delete localPath;
    if(updateInfo)
        delete updateInfo;
}

void UpdateDialog::on_btnClose_clicked()
{
    hide();
}

void UpdateDialog::on_btnQuery_clicked()
{

    QueryUpgrade *query = new QueryUpgrade();

    query->start();
}

void UpdateDialog::on_btnDownload_clicked()
{

}

void UpdateDialog::on_btnInstall_clicked()
{

}

