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
 * $Rev: 35 $
 *
 * QWatch - analog watch with extended functionality
 * under GPL Licence
 *
 * Display simple calendar
 */

#ifndef CALENDAR_H
#define CALENDAR_H


#include <QtGui/QDialog>
#include "timezones.h"
#include "config/configuration.h"

#include "ui_calendar.h"

namespace Ui
{
    class CalendarDialogClass;
}

class CalendarDialog : public QDialog
{
    Q_OBJECT

public:
    CalendarDialog(QWidget *parent);
    ~CalendarDialog();
    Ui::CalendarDialogClass *ui;

private slots:
    void on_pushButton_clicked();
};

#endif // CALENDAR_H
