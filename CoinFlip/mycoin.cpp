#include "mycoin.h"

#include <QDebug>
#include <QTimer>

MyCoin::MyCoin (QString btnImgPath)
{
    //初始化定时器,用于金币翻转热销
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //按照传入路径完成金币的初始化
    QPixmap qPixmap;
    bool loadFlag = qPixmap.load(btnImgPath);
    if(!loadFlag)
    {
        qDebug() << "MyCoin : The Image is load fail!";
        return;
    }

    this->setFixedSize(qPixmap.width(), qPixmap.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(qPixmap);
    this->setIconSize(QSize(qPixmap.width(), qPixmap.height()));

    //定时器信号槽
    //金币正面翻转
    connect(timer1, &QTimer::timeout, [=](){
        QPixmap qPixmap;
        QString str = QString(":/res/Coin000%1.png").arg((this->min)++);
        qPixmap.load(str);
        this->setFixedSize(qPixmap.width(),qPixmap.height() );
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(qPixmap);
        this->setIconSize(QSize(qPixmap.width(),qPixmap.height()));
        if(this->min > this->max) //如果大于最大值，重置最小值，并停止定时器
        {
            this->min = 1;
            this->isAnimation = false;  //动画结束,可以点击
            timer1->stop();
        }
    });

    //金币反面翻转
    connect(timer2, &QTimer::timeout, [=](){
        QPixmap qPixmap;
        QString str = QString(":/res/Coin000%1.png").arg((this->max)--);
        qPixmap.load(str);
        this->setFixedSize(qPixmap.width(),qPixmap.height() );
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(qPixmap);
        this->setIconSize(QSize(qPixmap.width(),qPixmap.height()));
        if(this->max < this->min) //如果大于最大值，重置最小值，并停止定时器
        {
            this->max = 8;
            this->isAnimation = false;  //动画结束,可以点击
            timer2->stop();
        }
    });
}

void MyCoin::mousePressEvent(QMouseEvent  *ev)
{
    //如果在完成动画期间继续点击,则直接返回,否则继续执行当前点击事件
    //当按钮变成成功标示后,禁用继续点击
    if(this->isAnimation || this->winFlag)
    {
        return;
    }
    else
    {
        return QPushButton::mousePressEvent(ev);
    }
}

void MyCoin::changeFlag()
{
    //如果是正面
    if(flag)
    {
        timer1->start(30);
        this->isAnimation = true;
        this->flag = false;
    }else {
        timer2->start(30);
        this->isAnimation = true;
        this->flag = true;
    }
}
