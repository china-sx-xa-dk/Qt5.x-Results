#include "mypushbutton.h"

#include <QDebug>
#include <QPropertyAnimation>

MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{

    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;

    //加载传入的图片
    QPixmap qPixmap;
    bool loadFlag = qPixmap.load(normalImg);
    if(!loadFlag)
    {
        qDebug() << "The Image is load fail!";
        return;
    }
    //设置固定尺寸
    this->setFixedSize(qPixmap.width(), qPixmap.height());

    //设置不规则图片的样式表
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标大小
    this->setIcon(qPixmap);

    //设置图标大小
    this->setIconSize(QSize(qPixmap.width(), qPixmap.height()));
}

//鼠标按下,更改按下图片
void MyPushButton::mousePressEvent(QMouseEvent *event)
{
    if(pressImgPath != "")
    {
        QPixmap qPixmap;
        bool loadFlag = qPixmap.load(pressImgPath);
        if(!loadFlag)
        {
            qDebug() << "mousePressEvent : The Image is load fail!";
            return;
        }
        //设置固定尺寸
        this->setFixedSize(qPixmap.width(), qPixmap.height());

        //设置不规则图片的样式表
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标大小
        this->setIcon(qPixmap);

        //设置图标大小
        this->setIconSize(QSize(qPixmap.width(), qPixmap.height()));
    }

    return QPushButton::mousePressEvent(event);
}

//鼠标释放,恢复正常图片
void MyPushButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(normalImgPath != "")
    {
        QPixmap qPixmap;
        bool loadFlag = qPixmap.load(normalImgPath);
        if(!loadFlag)
        {
            qDebug() << "mouseReleaseEvent : The Image is load fail!";
            return;
        }
        //设置固定尺寸
        this->setFixedSize(qPixmap.width(), qPixmap.height());

        //设置不规则图片的样式表
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标大小
        this->setIcon(qPixmap);

        //设置图标大小
        this->setIconSize(QSize(qPixmap.width(), qPixmap.height()));
    }

    return QPushButton::mouseReleaseEvent(event);
}

//图标下沉
void MyPushButton::zoom1()
{
    QPropertyAnimation * animation1 = new QPropertyAnimation(this, "geometry");
    //设置事件间隔
    animation1->setDuration(200);
    //设置起始位置
    animation1->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    animation1->setEndValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
    //设置动画,弹跳式,类似弹性球
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    animation1->start();
}

//图标上浮
void MyPushButton::zoom2()
{
    QPropertyAnimation * animation1 = new QPropertyAnimation(this, "geometry");
    //设置事件间隔
    animation1->setDuration(200);
    //设置起始位置
    animation1->setStartValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
    animation1->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
    //设置动画,弹跳式,类似弹性球
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    animation1->start();
}
