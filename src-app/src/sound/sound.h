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
 * Sound provider
 */

#ifndef SOUND_H
#define SOUND_H

#include <QString>
#include <QObject>
#include <QThread>

class WavSound : public QThread {

public:
    /*
    * Plays wav sound from file/resource on Linux or Windows
    */
    static void playWav(const QString wavResource);

protected:
    WavSound(const QString wavFile);
    ~WavSound();
    void run();

    QString wavFile;
};

#endif
