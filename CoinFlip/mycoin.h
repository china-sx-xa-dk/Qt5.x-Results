#ifndef MYCOIN_H
#define MYCOIN_H

#include <QMainWindow>
#include <QPushButton>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyCoin(QWidget *parent = nullptr);
    MyCoin (QString btnImgPath);

    //金币信息
    int posX;   //  x轴
    int posY;   //  y轴
    bool flag = false;  //  正反面
    bool winFlag = false;   //  判断时候已经成功用来禁用成功后的按钮触发

    //翻金币效果
    void changeFlag();
    QTimer * timer1;
    QTimer * timer2;
    //翻转用的大小值设定
    int min = 1;
    int max = 8;

    //设定标示,在点击动画时不让继续进行点击
    bool isAnimation = false;

    //重写鼠标按下事件
    void mousePressEvent(QMouseEvent  *ev);

signals:

};

#endif // MYCOIN_H
