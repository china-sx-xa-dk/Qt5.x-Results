#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //编写构造方法
    MyPushButton(QString normalImg, QString pressImg = "");

    //正常图片
    QString normalImgPath;
    //点击响应后的图片
    QString pressImgPath;

    //图标下沉
    void zoom1();

    //图标上浮
    void zoom2();

    //重写鼠标点击方法
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:

};

#endif // MYPUSHBUTTON_H
