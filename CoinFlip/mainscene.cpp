#include "mainscene.h"
#include "ui_mainscene.h"

#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QSound>

#include "mypushbutton.h"

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //设置固定大小
    setFixedSize(320, 588);

    //设置应用图标
    setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //设置窗口标题
    setWindowTitle("DuKang带你翻金币");

    //点击退出完成程序退出
    connect(ui->actionquit, &QAction::triggered, [=](){
        this->close();
    });

    //创建start按钮
    MyPushButton * btn_start = new MyPushButton(":/res/MenuSceneStartButton.png");
    btn_start->setParent(this);
    btn_start->move(this->width() * 0.5 - btn_start->width() * 0.5, this->height() * 0.7);

    //创建关卡选择窗口
    chooseLevel = new ChooseLevelScene;

    //创建选择关卡的关闭信号完成跳转回主页面
    connect(chooseLevel, &ChooseLevelScene::chooseLevelClose, [=](){
        this->setGeometry(chooseLevel->geometry());
        this->show();
        chooseLevel->hide();
    });

    //添加点击start开始时候的音效
    QSound * startSound = new QSound(":/res/TapButtonSound.wav",this);

    //给start按钮绑定点击事件
    connect(btn_start, &QPushButton::clicked, [=](){
        btn_start->zoom1();
        btn_start->zoom2();

        //点击音效
        startSound->play();

        //延时0.5秒执行切换,展示start按钮的动效
        QTimer::singleShot(500, this, [=](){
            chooseLevel->setGeometry(this->geometry());
            this->hide();
            chooseLevel->show();
        });
    });
}

//重写画家
void MainScene::paintEvent(QPaintEvent *event)
{
    //创建画家
    QPainter qPainter(this);
    //创建绘图
    QPixmap qPixmap;

    qPixmap.load(":/res/PlayLevelSceneBg.png");
    //绘制背景图
    qPainter.drawPixmap(0,0,this->width(),this->height(),qPixmap);

    //绘制左上角游戏名称
    qPixmap.load(":/res/Title.png");
    //缩放一倍
    qPixmap = qPixmap.scaled(qPixmap.width() * 0.5, qPixmap.height() * 0.5);
    qPainter.drawPixmap(10,30,qPixmap.width(),qPixmap.height(),qPixmap);

}

MainScene::~MainScene()
{
    delete ui;
}

