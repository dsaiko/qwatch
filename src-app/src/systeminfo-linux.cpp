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
 * System information
 */

#include <QX11Info>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include "systeminfo.h"

bool SystemInfo::canDrawTransparentWidgets() {
    static Display *display = QX11Info::display();
    static Atom compositeManagerAtom = XInternAtom(display, "_NET_WM_CM_S0",False);

    return XGetSelectionOwner(display,compositeManagerAtom);
}
