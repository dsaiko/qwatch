# QWatch project file - tests
# (c) Dusan Saiko dusan.saiko@gmail.com
# $Rev$
# $Id$

TEMPLATE = app
QT += testlib xml
TARGET = qwatch-tests

OBJECTS_DIR = ../build/tests
MOC_DIR = ../build/tests
UI_DIR = ../build/tests
RCC_DIR = ../build/tests
DESTDIR = ../build

INCLUDEPATH += . ../src-app/ ../src-app/src src/

HEADERS += src/qwatch-tests.h
SOURCES += src/qwatch-tests.cpp


HEADERS += ../src-app/src/qwatch.h \
    ../src-app/src/graphics/alarmanimation.h \
    ../src-app/src/graphics/painter.h \
    ../src-app/src/config/configuration.h \
    ../src-app/src/menu/second-timezone.h \
    ../src-app/src/menu/set-alarmclock.h \
    ../src-app/src/menu/calendar.h \
    ../src-app/src/menu/about.h \
    ../src-app/src/timezones.h \
    ../src-app/src/version.h \
    ../src-app/src/graphics/constants-graphics.h \
    ../src-app/src/config/constants-config.h \
    ../src-app/src/constants-app.h \
    ../src-app/src/sound/sound.h \
    ../src-app/src/systeminfo.h

SOURCES += \
    ../src-app/src/graphics/painter.cpp \
    ../src-app/src/graphics/painter-clock.cpp \
    ../src-app/src/graphics/painter-secondtime.cpp \
    ../src-app/src/graphics/painter-alarmclock.cpp \
    ../src-app/src/graphics/painter-trayicon.cpp \
    ../src-app/src/qwatch.cpp \
    ../src-app/src/version.cpp \
    ../src-app/src/config/configuration.cpp \
    ../src-app/src/menu/menu.cpp \
    ../src-app/src/menu/menu-actions.cpp \
    ../src-app/src/menu/set-alarmclock.cpp \
    ../src-app/src/menu/calendar.cpp \
    ../src-app/src/menu/about.cpp \
    ../src-app/src/timezones.cpp \
    ../src-app/src/systeminfo.cpp \
    ../src-app/src/graphics/alarmanimation.cpp \
    ../src-app/src/sound/sound.cpp \
    ../src-app/src/menu/second-timezone.cpp

win32 {
    LIBS    +=  -lwinmm
    LIBS += -lwininet
    LIBS += -lole32
    RC_FILE =   ../src-app/res/qwatch.rc

    SOURCES +=  ../src-app/src/update/inet.cpp ../src-app/src/update/md5.cpp ../src-app/src/menu/update.cpp ../src-app/src/update/query-upgrade.cpp ../src-app/src/update/download-upgrade.cpp
    HEADERS +=  ../src-app/src/update/inet.h ../src-app/src/update/md5.h ../src-app/src/menu/update.h ../src-app/src/update/query-upgrade.h ../src-app/src/update/download-upgrade.h
    FORMS += ../src-app/ui/update.ui

    DEFINES += _WIN32_WINNT=0x0500
}

unix {
    QMAKE_LIBS += -lasound
}

FORMS += ../src-app/ui/second-timezone.ui ../src-app/ui/set-alarmclock.ui ../src-app/ui/calendar.ui ../src-app/ui/about.ui

RESOURCES += ../src-app/res/resources.qrc
