#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
//    explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int levelNum);

    //关卡数
    int levelIndex;
    //胜利标示
    bool winFlag = false;
    //关卡的游戏信息
    QVector< QVector<int> > gameData;
    //金币数组数据保存,完成点击金币的周围金币的翻转
    MyCoin * myCoin[4][4];

    //重写画家事件
    void paintEvent(QPaintEvent *event);

signals:
    void playSceneClose();
};

#endif // PLAYSCENE_H
