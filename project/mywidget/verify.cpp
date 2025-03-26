#include "verify.h"
#include <QPainter>
#include <QPen>
#include <QFont>
#include <QColor>
#include <QFrame>
#include <QTime>

Verify::Verify()
{
    //验证码窗口初始化
    this->setFixedSize(150,55);
    this->setStyleSheet("background-color:white;");
    this->setLineWidth(0.5);
    this->setMidLineWidth(1);
//    this->setFrameShape(QFrame::Box);
//    this->setFrameShadow(QFrame::Raised);

    //随机数种子初始化
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    //生成随机数
    this->generateRandNum();
}

void Verify::generateRandNum()
{
    this->code.clear();
    for(int i = 0;i < 4;++i)
    {
        int num = qrand()%3;
        if(num == 0)
        {
            //数字
            this->code += QString::number(qrand()%10);
        }
        else if(num == 1)
        {
            //大写字母
            int temp = 'A';
            this->code += static_cast<QChar>(temp + qrand()%26);
        }
        else if(num == 2)
        {
            //小写字母
            int temp = 'a';
            this->code += static_cast<QChar>(temp + qrand()%26);
        }
    }
}

void Verify::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    QFont font("楷体",16,QFont::Bold,true);
    painter.setFont(font);

    //画点
    for(int i=0;i<100;i++)
    {
        pen = QPen(QColor(qrand()%256,qrand()%256,qrand()%256));
        painter.setPen(pen);
        painter.drawPoint(qrand()%180,qrand()%80);
    }

    //画线
    for(int i=0;i<5;i++)
    {
        pen = QPen(QColor(qrand()%256,qrand()%256,qrand()%256));
        painter.setPen(pen);
        painter.drawLine(qrand()%180,qrand()%80,qrand()%180,qrand()%80);
    }

    //绘制验证码
    for(int i=0;i<4;i++)
    {
        pen = QPen(QColor(qrand()%255,qrand()%255,qrand()%255));
        painter.setPen(pen);
        painter.drawText(15+35*i,10+qrand()%15,30,40,Qt::AlignCenter, QString(code[i]));
    }
}

void Verify::mousePressEvent(QMouseEvent *event)
{
    //重新生成验证码
    generateRandNum();
    //实时更新
    update();
}

QString Verify::getCode() const
{
    return code;
}

void Verify::setCode(const QString &value)
{
    code = value;
}

void Verify::updateVer()
{
    //重新生成验证码
    generateRandNum();
    //实时更新
    update();
}
