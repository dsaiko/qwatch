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

#include "menu/about.h"
#include "version.h"
#include "config/constants-config.h"
#include "qwatch.h"
#include <QDebug>
#include <QDate>
#include <QPixmap>

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::AboutDialogClass)
{
    ui->setupUi(this);

    ui->label->setPixmap(QPixmap(":/about-logo.jpg"));
    ui->textBrowser_2->viewport()->setAutoFillBackground(false);

    QDate versionDate = getVersionDate();
    QString date=versionDate.toString(Qt::DefaultLocaleShortDate);
    QString fullYear=versionDate.toString("yyyy");
    QString shortYear=versionDate.toString("yy");
    if(date.contains(fullYear) == false) {
        date = date.replace(shortYear,fullYear);
    }
    QString html = ui->textBrowser_2->toHtml().replace("VERSIONINFO",(getVersion()+" ("+date+")"));
#ifdef INTERSHOP
    html=html.replace("QWatch",QString("Intershop ")+STR_APPTITLE);
#endif

    ui->textBrowser_2->setHtml(html);
}


AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_pushButton_3_clicked()
{
    hide();
}
