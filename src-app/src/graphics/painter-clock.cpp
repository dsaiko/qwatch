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
 *
 * QWatch - analog watch with extended functionality
 * under GPL Licence
 *
 * Clock painting functions
 */

#include <QtGui>

#include "qwatch.h"
#include "graphics/painter.h"
#include "graphics/constants-graphics.h"


void drawPath(QPainter *painter, QFont font, QRect rect, int y, QString str)
{
    QPainterPath path;
    painter->setFont(font);
    QFontMetrics fm = painter->fontMetrics();
    int stringwidth = fm.width(str);
    path.addText(rect.left()+(rect.width()-stringwidth)/2, y, font, str);
    painter->drawPath(path);
}


void ClockPainter::paintClock(QWatch *app, QPainter *painter, QTime time, int size, int secondtimeoffset, bool trayiconmode) {

    static const QPen borderPenNormal(QColor(0,0,0,32),2);
    static const QPen borderPenTrayIcon(QColor(0,0,0,192),1);

    static const QPen   handBorderThick(QColor(0, 0, 0, 20),4);
    static const QPen   borderBlack(QColor(0, 0, 0, 255),1);
    static const QPen   handBorderSmall(QColor(0, 0, 0, 20),2);

    static const QColor hourColor(0,224,127,20);
    static const QColor minuteColor(255,255,0,20);
    static const QColor secondsColor(230, 0, 0, 20);


    static const QFont font2("verdana",7,0);
    static const QColor alarmRed(192,0,0,255);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->translate(size / 2, size / 2);

    painter->setPen(trayiconmode ? borderPenTrayIcon : borderPenNormal);
    painter->setBrush(*gradient);
    painter->drawEllipse(-size/2 + 1, -size/2 +1, size-2, size-2);


    painter->setPen(Qt::NoPen);

    painter->scale(size / 200.0, size / 200.0);

      if(trayiconmode) {
        static QColor back1(224,243,255,190);
        painter->setBrush(back1);
        painter->setPen(Qt::NoPen);
        painter->drawEllipse(-100, -100, 200, 200);

        static QColor back2(224*4/5,243*4/5,255*4/5,150);
        painter->setBrush(back2);
        painter->drawEllipse(-10, -10, 80, 80);

    }

    paintStripes(painter);


  if(trayiconmode) {
#define delta 20
#define delta2 10
        static QPen pen44(QColor(192,192,120,255),delta);
        painter->setPen(pen44);
        painter->setBrush(Qt::NoBrush);
        painter->drawEllipse(-100+delta, -100+delta, 200-delta*2, 200-delta*2);
        static QPen pen44b(QColor(0,0,0,192),delta2);
        painter->setPen(pen44b);
        painter->drawEllipse(-100+delta2, -100+delta2, 200-delta2*2, 200-delta2*2);
        static QPen pen44c(QColor(255,255,255,255),delta2);
        painter->setPen(pen44c);
        painter->drawArc(-100+delta2, -100+delta2, 200-delta2*2, 200-delta2*2, 5760/8, 5760/2);
    }


    if(trayiconmode == false)  {
        painter->setPen(trayiconmode ? borderBlack : handBorderThick);
        painter->setBrush(trayiconmode ? Qt::black :  hourColor);
        drawHand(painter, 30.0 * ((time.hour() + time.minute() / 60.0)), hourHand, 8, false);

        painter->setPen(trayiconmode ? borderBlack : handBorderThick);
        painter->setBrush(trayiconmode ? Qt::black :   minuteColor);
        drawHand(painter, 6.0 * (time.minute() + time.second() / 60.0), minuteHand, 8, false);

        painter->setPen(handBorderSmall);
        painter->setBrush(secondsColor);
        drawHand(painter, 6.0 * (time.second()), secondsHand, 6, false);

        paintDate(painter);
        paintAlarmClock(app, painter, app->alarmTime, -44, 0);

        QTime t2 = time.addSecs(secondtimeoffset);
        paintSecondClock(painter, t2, 0, -41);

        static const QRect r1(32, -51, 15, 15);
        drawPath(painter, font2, r1, r1.bottom(), "T2");
        paintLogo(painter);

        if(app->enableAlarmClockAction->isChecked()) {
            painter->setBrush(alarmRed);
        }
        static const QRect r3(-68, 25, 50, 11);
        drawPath(painter, font2, r3, r3.bottom(), "ALR");

        paintDigits(painter,trayiconmode);
    }

    if(trayiconmode)  {
        painter->setPen(trayiconmode ? borderBlack : handBorderThick);
        painter->setBrush(trayiconmode ? Qt::black :  hourColor);
        drawHand(painter, 30.0 * ((time.hour() + time.minute() / 60.0)), hourHand2, 8, false);

        painter->setPen(trayiconmode ? borderBlack : handBorderThick);
        painter->setBrush(trayiconmode ? Qt::black :   minuteColor);
        drawHand(painter, 6.0 * (time.minute() + time.second() / 60.0), minuteHand2, 8, false);
    }

    //animation
    if(app->alarmAnimation->isRunning && trayiconmode == false) {
        painter->setBrush(QColor(255,255,0,app->alarmAnimation->alarmAnimationStep/2));
        painter->setPen(Qt::NoPen);
        painter->drawEllipse(-90, -90, 180, 180);
    }


    //time marks at the clock ring

    static const QPen timeMarkColor1(QColor(0,0,0, 224),1);
    static const QPen timeMarkColor2(QColor(0,0,0, 224),3);
    static const QPen timeMarkColor2b(QColor(0,0,0, 180),10);

    for (int j = 0; j < 60; ++j) {
        if(j % 5 == 0) {
            painter->setPen(trayiconmode ? timeMarkColor2b : timeMarkColor2);
        } else {
            if(trayiconmode) {
                painter->setPen(Qt::NoPen);
            } else {
               painter->setPen(timeMarkColor1);
            }
        }
        painter->drawLine(trayiconmode ? 90 : 95, 0, trayiconmode ? 95 : 97, 0);
        painter->rotate(6.0);
    }


}


void ClockPainter::paintDate(QPainter *painter) {
    static const QFont font("arial black",12,900);
    static const QFont font2("arial black",8,900);

    painter->setFont(font);

    static const QColor brushField(255,255,255,164);
    static const QPen borderField(QColor(100,100,100,100),1);
    static const QColor penText(0,0,0,220);

    painter->setPen(borderField);
    painter->setBrush(brushField);
    QRect rect(-10, 5, 80, 18);
    painter->drawRect(rect);

    QString date=QTime::currentTime().toString(Qt::DefaultLocaleLongDate).split(" ").first();

    painter->setPen(Qt::NoPen);
    painter->setBrush(penText);

    drawPath(painter, font, rect, rect.bottom()-2, date);

    painter->setFont(font2);
    QDate currentDate=QDate::currentDate();
    QString date2=currentDate.toString(Qt::DefaultLocaleShortDate);
    QString fullYear=currentDate.toString("yyyy");
    QString shortYear=currentDate.toString("yy");
    if(date2.contains(fullYear) == false) {
        date2 = date2.replace(shortYear,fullYear);
    }
    QRect rect2(-10, 25, 80, 10);
    drawPath(painter, font2, rect2, rect2.bottom(), date2);

}

void ClockPainter::paintStripes(QPainter *painter) {
    painter->save();
    static const QColor stripecolor(0,0,0,10);

    painter->rotate(30);

    painter->setBrush(stripecolor);
    painter->drawRect(-85,-22,170,22);
    painter->drawRect(-85,6,170,22);

    painter->rotate(60);
    painter->drawRect(-85,-22,170,22);
    painter->drawRect(-85,6,170,22);
    painter->rotate(60);
    painter->drawRect(-85,-22,170,22);
    painter->drawRect(-85,6,170,22);
    painter->restore();

    painter->setBrush(Qt::NoBrush);
    static QColor datePen2(0,0,0,10);
    painter->setPen(datePen2);
    for(int i=10; i<=80; i+=5) {
        painter->drawEllipse(-i,-i,i*2,i*2);
    }
}

void ClockPainter::paintLogo(QPainter *painter) {

    painter->save();

    static const QFont font2("verdana",6,0);
    painter->setFont(font2);
    static const QString  str("Water Resistant");

    QRect rect(-5,-5,70,10);
    drawPath(painter,font2,rect,rect.bottom()-2,str);

    static const QFont font3("arial black",10,900);
    painter->setFont(font3);

    static QColor c1(192,0,0,192);
    painter->setPen(Qt::NoPen);
    painter->setBrush(c1);


#ifdef INTERSHOP
    static QString str2("INTERSHOP");
    painter->rotate(40);
    int offset = 70;
#else
    static QString str2("QWATCH");
    painter->rotate(24);
    int offset=65;
#endif

    QFontMetrics fm = painter->fontMetrics();
    for(int i=0; i<str2.length(); i++) {
        QCharRef c = str2[i];
        int w = fm.width(c);

        QPainterPath path2;
        path2.addText(-w/2, offset, font3, QString(c));
        painter->drawPath(path2);
#ifdef INTERSHOP
        if(i==0) {
            painter->rotate(-w*2);
        } else {
            painter->rotate(-w*1);
        }
#else
        painter->rotate(-w*1);
#endif
    }
    painter->restore();
}

void ClockPainter::paintDigits(QPainter *painter, bool trayiconmode) {
    static const QFont fontD1("arial black",11,900);
    static const QFont fontD2("arial black",12,900);
    static QPen stroke(QColor(0,0,0,162),1);
    static QColor brush(240,240,240,255);
    static QColor brush2(250,250,250,255);
    static QColor brushDigitsTrayIcon(0,0,0,255);


    painter->setFont(fontD1);
    painter->setPen(stroke);
    painter->setBrush(brush);


    painter->rotate(30.0);
    for (int i = 1; i < 12; i+=1) {
        if(i<3 || i > 9) {
            QString str = QString("%1").arg(i==0?12:i);
            painter->setPen(stroke);
            painter->setBrush(brush);

            QPainterPath path2;
            int w = painter->fontMetrics().width(str);
            path2.addText(QPoint(-w/2, -75), fontD1, str);

            painter->drawPath(path2);
        }
            painter->rotate(30.0);
    }
    painter->save();
    painter->rotate(180.0);
    painter->setPen(stroke);
    painter->setBrush(brush);

    for (int i = 0; i < 12; i+=1) {
        if(i>3 && i < 9 && i != 6) {
            QString str = QString("%1").arg(i==0?12:i);

            QPainterPath path2;
            int w = painter->fontMetrics().width(str);
            path2.addText(QPoint(-w/2, 85), fontD1, str);

            painter->drawPath(path2);
        }
        painter->rotate(30.0);
    }
    painter->restore();

    painter->setPen(stroke);
    painter->setBrush(trayiconmode ? brushDigitsTrayIcon : brush2);

    {
         QPainterPath path2;
         const static QString str("3");
         path2.addText(QPoint(75, 6), fontD2, str);

         painter->drawPath(path2);
    }
    {
         QPainterPath path2;
         const static QString str("9");
         path2.addText(QPoint(-84, 6), fontD2, str);

         painter->drawPath(path2);
    }
    {
         QPainterPath path2;
         const static QString str("12");
         path2.addText(QPoint(-13, -73), fontD2, str);

         painter->drawPath(path2);
    }
    {
         QPainterPath path2;
         const static QString str("6");
         path2.addText(QPoint(-6, 86), fontD2, str);

         painter->drawPath(path2);
    }
}
