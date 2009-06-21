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
 * Logo configuration
 */

#include "menu/logo.h"
#include "config/constants-config.h"
#include "graphics/constants-graphics.h"
#include "qwatch.h"
#include <QMessageBox>
#include <QLocale>


LogoDialog::LogoDialog(QWatch *parent)
    : QDialog(parent), ui(new Ui::LogoDialogClass)
{
    ui->setupUi(this);
    this->qwatch = parent;
    ui->lineEdit->setText(qwatch->configuration->getString(CONFIG_LOGO,LOGO_DEFAULT));
}


LogoDialog::~LogoDialog()
{
    delete ui;
}

void LogoDialog::on_pushButton_clicked()
{
    hide();
    qwatch->configuration->setString(CONFIG_LOGO,ui->lineEdit->text());
}

void LogoDialog::on_pushButton_2_clicked()
{
    hide();
    ui->lineEdit->setText(qwatch->configuration->getString(CONFIG_LOGO,LOGO_DEFAULT));
}
