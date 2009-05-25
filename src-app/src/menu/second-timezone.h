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
 * $Rev: 37 $
 *
 * QWatch - analog watch with extended functionality
 * under GPL Licence
 *
 * Configuration dialog for selecting second Time Zone
 */

#ifndef SECOND_TIMEZONE_H
#define SECOND_TIMEZONE_H


#include <QtGui/QDialog>
#include "timezones.h"
#include "config/configuration.h"

#include "ui_second-timezone.h"

namespace Ui
{
    class SecondTimeDialogClass;
}

class SecontTimeZoneDialog : public QDialog
{
    Q_OBJECT

public:
    SecontTimeZoneDialog(QWidget *parent, TimeZones *timeZones, Configuration *c);
    ~SecontTimeZoneDialog();

private:
    Ui::SecondTimeDialogClass *ui;
    Configuration *config;

protected slots:
    void setSecondTimeZone();

signals:
    void timeZoneChanged();

    friend class QWatch;
};

#endif // SECOND_TIMEZONE_H
