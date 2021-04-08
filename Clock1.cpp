#include "Clock1.h"

Clock1::Clock1(QWidget *parent)
    : QDialog(parent)
{
    //初始化变量
    hour=0;
    minute=0;
    second=0;
    //设置窗口大小
    setFixedSize(600,600);
    //去掉问号
    Qt::WindowFlags flags= this->windowFlags();
    setWindowFlags(flags&~Qt::WindowContextHelpButtonHint);
    //背景设置成白色
    QPalette bgpal=palette();
    bgpal.setColor(QPalette::Background,QColor(255,255,255));
    setPalette(bgpal);
    //设置定时器
    startTimer(1000);
    //执行一次绘图
    QTime curr_time =QTime::currentTime();
    second=curr_time.second();
    minute=curr_time.minute()+second/60;
    hour=curr_time.hour()+minute/60;
}

Clock1::~Clock1(){}

#include <QDebug>

void Clock1::timerEvent(QTimerEvent*)
{
    QTime curr_time=QTime::currentTime();
    second=curr_time.second();
    minute=curr_time.minute()+second/60;
    hour=curr_time.hour()+minute/60;
    update();
}

void Clock1::paintEvent(QPaintEvent*)
{
    //初始化画图对象
    QPainter painter(this);
    //绘图坐标移动到中心
    int width=this->width();
    int height=this->height();
    painter.translate(width>>1,height>>1);
    int radius=((width>height)?height:width)/2-30;
    //启用反锯齿
    painter.setRenderHint(QPainter::Antialiasing, true);
    //取消画笔
    painter.setPen(Qt::NoPen);
    //绘制第一层圆环
    DrawCircularRing1(painter,radius,radius-4);
    //绘制第二层圆环
    DrawCircularRing2(painter,radius-4,radius-20);
    //绘制第三层圆环
    DrawCircularRing3(painter,radius-20,radius-25);
    //绘制表盘刻度线
    DrawScaleLine(painter,radius-35);
    //绘制表盘上数字
    DrawDialNumber(painter,radius-70);
    //绘制时针
    DrawHourPointer(painter,radius-150);
    //绘制分针
    DrawMinutePointer(painter,radius-120);
    //绘制秒针
    DrawSecondPointer(painter,radius-100);
}

void Clock1::DrawCircularRing1(QPainter& painter,int radius1,int radius2)
{
    //保存绘图对象
    painter.save();
    //计算大小圆路径
    QPainterPath outRing;
    QPainterPath inRing;
    outRing.moveTo(0,0);
    inRing.moveTo(0,0);
    outRing.addEllipse(-radius1,-radius1, 2*radius1,2*radius1);
    inRing.addEllipse(-radius2,-radius2,2*radius2,2*radius2);
    outRing.closeSubpath();
    //设置画刷
    painter.setBrush(QColor(200,200,200));
    //大圆减去小圆得到圆环
    painter.drawPath(outRing.subtracted(inRing));
    //恢复绘图对象
    painter.restore();
}

void Clock1::DrawCircularRing2(QPainter& painter,int radius1,int radius2)
{
    //保存绘图对象
    painter.save();
    //计算大小圆路径
    QPainterPath outRing;
    QPainterPath inRing;
    outRing.moveTo(0,0);
    inRing.moveTo(0,0);
    outRing.addEllipse(-radius1,-radius1, 2*radius1,2*radius1);
    inRing.addEllipse(-radius2,-radius2,2*radius2,2*radius2);
    outRing.closeSubpath();
    //设置画刷
    painter.setBrush(QColor(235,235,235));
    //大圆减去小圆得到圆环
    painter.drawPath(outRing.subtracted(inRing));
    //恢复绘图对象
    painter.restore();
}

void Clock1::DrawCircularRing3(QPainter& painter,int radius1,int radius2)
{
    //保存绘图对象
    painter.save();
    //计算大小圆路径
    QPainterPath outRing;
    QPainterPath inRing;
    outRing.moveTo(0,0);
    inRing.moveTo(0,0);
    outRing.addEllipse(-radius1,-radius1, 2*radius1,2*radius1);
    inRing.addEllipse(-radius2,-radius2,2*radius2,2*radius2);
    outRing.closeSubpath();
    //设置画刷
    painter.setBrush(QColor(180,180,180));
    //大圆减去小圆得到圆环
    painter.drawPath(outRing.subtracted(inRing));
    //恢复绘图对象
    painter.restore();
}

void Clock1::DrawScaleLine(QPainter& painter,int radius)
{
    //设置画刷
    painter.setBrush(QColor(100,100,100));
    //组装点的路径图
    QPainterPath pointPath1;
    pointPath1.moveTo(-2,-2);
    pointPath1.lineTo(-1,-4);
    pointPath1.lineTo(1,-4);
    pointPath1.lineTo(2,-2);
    pointPath1.lineTo(1,8);
    pointPath1.lineTo(-1,8);
    QPainterPath pointPath2;
    pointPath2.moveTo(-2,-2);
    pointPath2.lineTo(-1,-4);
    pointPath2.lineTo(1,-4);
    pointPath2.lineTo(2,-2);
    pointPath2.lineTo(1,20);
    pointPath2.lineTo(-1,20);
    //绘制25个刻度
    for(int i=0;i<60;++i){
        QPointF point(0,0);
        painter.save();
        //计算并移动绘图对象中心点
        point.setX(radius*qCos(((90-i*6)*M_PI)/180));
        point.setY(radius*qSin(((90-i*6)*M_PI)/180));
        //计算并移动绘图对象的中心点
        painter.translate(point.x(),-point.y());
        //计算并选择绘图对象坐标
        painter.rotate(i*6);
        //绘制路径
        if(i%5){
            painter.drawPath(pointPath1);
        }
        else{
            painter.drawPath(pointPath2);
        }
        painter.restore();
    }
}

void Clock1::DrawDialNumber(QPainter& painter,int radius)
{
    painter.setPen(QColor(100,100,100));
    QFont font;
    font.setFamily("SimHei");
    font.setPointSize(16);
    painter.setFont(font);
    //绘制13个小点
    for(int i=0;i<12;++i){
        QPointF point(0,0);
        painter.save();
        //计算并移动绘图对象中心点
        point.setX(radius*qCos(((60-i*30)*M_PI)/180));
        point.setY(radius*qSin(((60-i*30)*M_PI)/180));
        //计算并移动绘图对象的中心点
        painter.translate(point.x(),-point.y());
        //绘制路径
        painter.drawText(-15, -15, 30, 30,Qt::AlignCenter,QString::number(i+1));
        painter.restore();
    }
}

void Clock1::DrawHourPointer(QPainter& painter,int radius)
{
    painter.setPen(Qt::NoPen);
    //组装点的路径图
    QPainterPath pointPath;
    pointPath.moveTo(10,0);
    pointPath.lineTo(1,-radius);
    pointPath.lineTo(-1,-radius);
    pointPath.lineTo(-10,0);
    pointPath.arcTo(-10,0,20,20,180,180);
    painter.save();
    //计算并选择绘图对象坐标
    painter.rotate(hour*30);
    //设置画刷
    painter.setBrush(QColor(0,0,0,200));
    //绘制路径
    painter.drawPath(pointPath);
    painter.restore();
}

void Clock1::DrawMinutePointer(QPainter& painter,int radius)
{
    //组装点的路径图
    QPainterPath pointPath;
    pointPath.moveTo(10,0);
    pointPath.lineTo(1,-radius);
    pointPath.lineTo(-1,-radius);
    pointPath.lineTo(-10,0);
    pointPath.arcTo(-10,0,20,20,180,180);
    painter.save();
    //计算并选择绘图对象坐标
    painter.rotate(minute*6);
    //设置画刷
    painter.setBrush(QColor(0,0,0,200));
    //绘制路径
    painter.drawPath(pointPath);
    painter.restore();
}

void Clock1::DrawSecondPointer(QPainter& painter,int radius)
{
    //组装点的路径图
    QPainterPath pointPath;
    pointPath.moveTo(10,0);
    pointPath.lineTo(1,-radius);
    pointPath.lineTo(-1,-radius);
    pointPath.lineTo(-10,0);
    pointPath.arcTo(-10,0,20,20,180,180);
    QPainterPath inRing;
    inRing.addEllipse(-5,-5,10,10);
    painter.save();
    //计算并选择绘图对象坐标
    painter.rotate(second*6);
    //设置画刷
    painter.setBrush(QColor(255,0,0,200));
    //绘制路径
    painter.drawPath(pointPath.subtracted(inRing));
    painter.restore();
}
