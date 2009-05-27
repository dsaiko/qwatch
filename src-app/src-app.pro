# QWatch project file - application
# (c) Dusan Saiko dusan.saiko@gmail.com
# $Rev$


TEMPLATE =      app
QT +=           xml
TARGET =        qwatch
INCLUDEPATH +=  . src/

#ISBUILD DEFINES += INTERSHOP
#ISBUILD TARGET = iswatch

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

win32 {
    SOURCES +=  src/timezones-win.cpp \
                src/systeminfo-win.cpp

    LIBS    +=  -lwinmm
    RC_FILE =   res/qwatch.rc
}


unix { 

SOURCES +=      src/timezones-linux.cpp \
                src/systeminfo-linux.cpp \

QMAKE_LIBS +=   -lasound
}

FORMS +=        ui/second-timezone.ui \
                ui/set-alarmclock.ui \
                ui/calendar.ui \
                ui/about.ui

RESOURCES +=    res/resources.qrc


TRANSLATIONS =  ../lang/qwatch_cs.ts \
                ../lang/qwatch_en.ts \
                ../lang/qwatch_de.ts
