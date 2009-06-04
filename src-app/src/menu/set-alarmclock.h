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

#ifndef SET_ALARMCLOCK_H
#define SET_ALARMCLOCK_H


#include <QtGui/QDialog>
#include "config/configuration.h"

#include "ui_set-alarmclock.h"

namespace Ui
{
    class SetAlarmClockDialogClass;
}

class SetAlarmClockDialog : public QDialog
{
    Q_OBJECT

public:
    SetAlarmClockDialog(QWidget *parent, Configuration *config);
    ~SetAlarmClockDialog();
    void setDefaults();

private:
    Ui::SetAlarmClockDialogClass *ui;
    Configuration *config;

protected slots:
    void setAlarmClock();

signals:
    void alarmTimeChanged(QTime time);


private slots:
    void on_pushButton_2_clicked();
    void on_comboBoxMinutes_highlighted(int index);
    void on_comboBoxHours_highlighted(int index);
    void on_comboBoxMinutes2_highlighted(int index);

    friend class QWatch;
};

#endif // SET_ALARMCLOCK_H
