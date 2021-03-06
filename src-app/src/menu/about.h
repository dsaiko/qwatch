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

#ifndef ABOUTDLG_H
#define ABOUTDLG_H


#include <QtGui/QDialog>
#include "timezones.h"
#include "config/configuration.h"

#include "ui_about.h"

namespace Ui
{
    class AboutDialogClass;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    AboutDialog(QWidget *parent);
    ~AboutDialog();
    Ui::AboutDialogClass *ui;
    void setVersion();

private slots:
    void on_pushButton_3_clicked();
};

#endif // ABOUTDLG_H
