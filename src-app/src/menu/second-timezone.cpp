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
 * Configuration dialog for selecting second Time Zone
 */

#include "menu/second-timezone.h"
#include "config/constants-config.h"

SecontTimeZoneDialog::SecontTimeZoneDialog(QWidget *parent, TimeZones *timeZones, Configuration *c)
    : QDialog(parent), ui(new Ui::SecondTimeDialogClass)
{
    ui->setupUi(this);

    config = c;
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(setSecondTimeZone()));

    ui->comboBox->addItem("","");
    QList<QString> *zones=timeZones->listTimeZones();

    if(zones != NULL) {
        foreach(QString zone, *zones) {
            QString zoneText = zone;
            zoneText.replace('_',' ');
            zone.replace(" ","");
            ui->comboBox->addItem(zoneText, zone);
        }
    }
}


void SecontTimeZoneDialog::setDefaults() {
    QString currentTZ = config->getString(CONFIG_SECONDTIMEZONE,"");
    QString label = config->getString(CONFIG_SECONDTIMEZONE_LABEL,"");

    if(currentTZ.length()>0) {
        int dataIndex = ui->comboBox->findData(currentTZ);
        if(dataIndex != -1) {
            ui->comboBox->setCurrentIndex(dataIndex);
        } else {
            config->setString(CONFIG_SECONDTIMEZONE,"");
        }
    } else {
        ui->comboBox->setCurrentIndex(0);
    }

    ui->editLabel->setText(label);
}

void SecontTimeZoneDialog::setSecondTimeZone()
{
    QString data = ui->comboBox->itemData(ui->comboBox->currentIndex()).toString();
    data.replace(" ","");
    config->setString(CONFIG_SECONDTIMEZONE,data);

    config->setString(CONFIG_SECONDTIMEZONE_LABEL,ui->editLabel->text());

    hide();
    emit timeZoneChanged();
}

SecontTimeZoneDialog::~SecontTimeZoneDialog()
{
    delete ui;
}

void SecontTimeZoneDialog::on_pushButton_2_clicked()
{
    hide();
}
