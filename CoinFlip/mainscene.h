#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>

#include "chooselevelscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    //选择关卡窗口
    ChooseLevelScene * chooseLevel;

    //重写画家事件
    void paintEvent(QPaintEvent *event);

private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H
