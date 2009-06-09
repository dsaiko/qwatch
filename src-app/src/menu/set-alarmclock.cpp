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
 * Configuration dialog for setting alarm clock
 */

#include "menu/set-alarmclock.h"
#include "config/constants-config.h"

SetAlarmClockDialog::SetAlarmClockDialog(QWidget *parent, Configuration *config)
    : QDialog(parent), ui(new Ui::SetAlarmClockDialogClass)
{
    ui->setupUi(this);
    this->config = config;

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(setAlarmClock()));
    setDefaults();
}

void SetAlarmClockDialog::setDefaults() {
    QString alarmTime = config->getString(CONFIG_ALARMCLOCK,"12:00");
    QStringList l = alarmTime.split(":");
    int h = l[0].toInt();
    int m = l[1].toInt();

    ui->comboBoxHours->clear();    
    for(int i=1; i<=12; i++) {
        QString val = QString::number(i);
        ui->comboBoxHours->addItem(val);
        if(h == i) {
            ui->comboBoxHours->setCurrentIndex(i-1);
        }
    }

    ui->comboBoxMinutes2->clear();
     for(int i=1; i<=99; i++) {
        QString val = QString::number(i);
        ui->comboBoxMinutes2->addItem(val);
    }

    ui->comboBoxMinutes->clear();
    for(int i=0; i<=60; i++) {
        QString val = QString::number(i);
        if(val.length()<2) {
            val = "0" + val;
        }
        ui->comboBoxMinutes->addItem(val);
        if(m == i) {
            ui->comboBoxMinutes->setCurrentIndex(i);
        }

    }

    ui->radioButtonAbsoluteTime->setChecked(true);
    //pack the layout
    setMaximumSize(10,10);
}

SetAlarmClockDialog::~SetAlarmClockDialog()
{
    delete ui;
}


void SetAlarmClockDialog::setAlarmClock()
{
    QTime alarmTime;

    if(ui->radioButtonAbsoluteTime->isChecked()) {
        int hour = ui->comboBoxHours->currentText().toInt();
        int min = ui->comboBoxMinutes->currentText().toInt();

        alarmTime.setHMS(hour, min, 0, 0);

        config->setString(CONFIG_ALARMCLOCK,ui->comboBoxHours->currentText()+":"+ui->comboBoxMinutes->currentText());
        hide();
        emit alarmTimeChanged(alarmTime,false,true);
    } else {
        QTime c = QTime::currentTime();

        int hour = c.hour();
        int min = c.minute() + ui->comboBoxMinutes2->currentText().toInt();

        while(min>59) {
            hour ++;
            min -= 60;
        }

        if(hour > 12) {
            hour -= 12;
        }

        config->setString(CONFIG_ALARMCLOCK,QString::number(hour)+":"+QString::number(min));

        alarmTime.setHMS(hour, min, c.second(), 0);

        hide();
        emit alarmTimeChanged(alarmTime,false,true);

    }
}

void SetAlarmClockDialog::on_comboBoxMinutes2_highlighted(int) {
     ui->radioButtonRelativeTime->setChecked(true);
}


void SetAlarmClockDialog::on_comboBoxHours_highlighted(int) {
     ui->radioButtonAbsoluteTime->setChecked(true);
}

void SetAlarmClockDialog::on_comboBoxMinutes_highlighted(int) {
     ui->radioButtonAbsoluteTime->setChecked(true);
}

void SetAlarmClockDialog::on_pushButton_2_clicked()
{
    hide();
}
