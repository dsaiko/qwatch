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
 * $Rev: 44 $
 *
 * QWatch - analog watch with extended functionality
 * under GPL Licence
 *
 */

#include <QApplication>
#include "qwatch.h"
#include "config/constants-config.h"
#include "sound/sound.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(resources);

    QApplication app(argc, argv);
    app.setApplicationName(STR_APPTITLE);

    QWatch *qwatch = new QWatch();
    qwatch->show();
    //workaround for qwatch to show up
    qwatch->move(qwatch->pos()+QPoint(1,1));

    WavSound::playWav(":/alarm.wav");
    return app.exec();
}
