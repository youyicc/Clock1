#ifndef CLOCK1_H
#define CLOCK1_H

#include <QTime>
#include <QtMath>
#include <QDialog>
#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>

class Clock1 : public QDialog
{
    Q_OBJECT

private:
    double hour;
    double minute;
    double second;

public:
    Clock1(QWidget *parent = nullptr);
    ~Clock1();

protected:
    virtual void timerEvent(QTimerEvent*);
    virtual void paintEvent(QPaintEvent*);

public:
    void DrawScaleLine(QPainter&,int);
    void DrawDialNumber(QPainter&,int);
    void DrawHourPointer(QPainter&,int);
    void DrawSecondPointer(QPainter&,int);
    void DrawMinutePointer(QPainter&,int);
    void DrawCircularRing1(QPainter&,int,int);
    void DrawCircularRing2(QPainter&,int,int);
    void DrawCircularRing3(QPainter&,int,int);
};
#endif
