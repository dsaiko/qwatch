# QWatch project file - application
# (c) Dusan Saiko dusan.saiko@gmail.com
# $Rev$
# $Id$


TEMPLATE =      app
QT +=           xml
TARGET =        qwatch
INCLUDEPATH +=  . src/

#ISBUILD DEFINES += INTERSHOP
#ISBUILD TARGET = iswatch

#64BUILD DEFINES += WINDOWS64

OBJECTS_DIR = ../build/app
MOC_DIR = ../build/app
UI_DIR = ../build/app
RCC_DIR = ../build/app
DESTDIR = ../build

HEADERS +=      src/qwatch.h \
                src/sound/sound.h \
                src/graphics/alarmanimation.h \
                src/graphics/painter.h \
                src/config/configuration.h \
                src/menu/second-timezone.h \
                src/menu/set-alarmclock.h \
                src/menu/calendar.h \
                src/menu/about.h \
                src/timezones.h \
                src/menu/logo.h \
                src/version.h \
                src/graphics/constants-graphics.h \
                src/config/constants-config.h \
                src/constants-app.h \
                src/systeminfo.h

SOURCES +=      src/main.cpp \
                src/graphics/painter.cpp \
                src/graphics/painter-clock.cpp \
                src/graphics/painter-secondtime.cpp \
                src/graphics/painter-alarmclock.cpp \
                src/graphics/painter-trayicon.cpp \
                src/qwatch.cpp \
                src/menu/logo.cpp \
                src/timezones.cpp \
                src/systeminfo.cpp \
                src/config/configuration.cpp \
                src/menu/menu.cpp \
                src/menu/menu-actions.cpp \
                src/menu/set-alarmclock.cpp \
                src/menu/calendar.cpp \
                src/menu/about.cpp \
                src/version.cpp \
                src/graphics/alarmanimation.cpp \
                src/sound/sound.cpp \
                src/menu/second-timezone.cpp

FORMS +=        ui/second-timezone.ui \
                ui/set-alarmclock.ui \
                ui/calendar.ui \
                ui/logo.ui \
                ui/about.ui

RESOURCES +=    res/resources.qrc


TRANSLATIONS =  ../lang/qwatch_cs.ts \
                ../lang/qwatch_en.ts \
                ../lang/qwatch_de.ts

win32 {
    LIBS    +=  -lwinmm
    LIBS += -lwininet
    LIBS += -lole32
    RC_FILE =   res/qwatch.rc

    SOURCES +=  src/update/inet.cpp src/update/md5.cpp src/menu/update.cpp src/update/query-upgrade.cpp src/update/download-upgrade.cpp
    HEADERS +=  src/update/inet.h src/update/md5.h src/menu/update.h src/update/query-upgrade.h src/update/download-upgrade.h
    FORMS += ui/update.ui

    DEFINES += _WIN32_WINNT=0x0500
}


unix {
    QMAKE_LIBS += -lasound -lX11
}
