#include "chooselevelscene.h"

#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QDebug>
#include <QSound>

#include "mypushbutton.h"

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //设置窗体的属性
    //设置固定大小
    setFixedSize(320, 588);

    //设置应用图标
    setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //设置窗口标题
    setWindowTitle("选择关卡");

    //设置菜单栏
    QMenuBar * qMenuBar = menuBar();
    QAction * qAction = qMenuBar->addMenu("开始")->addAction("退出");
    this->setMenuBar(qMenuBar);

    //点击退出完成程序退出
    connect(qAction , &QAction::triggered, [=](){
        this->close();
    });

    //创建back_btn
    MyPushButton * btn_back = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    btn_back->setParent(this);
    btn_back->move(this->width() - btn_back->width(), this->height() - btn_back->height());

    //返回按钮音效
    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);

    //点击返回按钮0.5秒后跳转回首页
    connect(btn_back, &QPushButton::clicked, [=](){
        backSound->play();
        QTimer::singleShot(500, this, [=](){
            emit this->chooseLevelClose();
        });
    });

    QSound *chooseSound = new QSound(":/res/TapButtonSound.wav",this);

    //创建关卡选择icon
    for(int i = 0; i < 20 ; i++)
    {
        MyPushButton * levelIcon = new MyPushButton(":/res/LevelIcon.png");
        levelIcon->setParent(this);
        levelIcon->move(25 + (i%4)*70 , 160 + (i/4)*70);

        //给按钮绑定点击事件
        connect(levelIcon, &QPushButton::clicked, [=](){
            //设置打开窗口音效
            chooseSound->play();

            //打开关卡窗口
            playScene = new PlayScene(i+1);
            this->hide();
            playScene->setGeometry(this->geometry());
            playScene->show();

            connect(playScene, &PlayScene::playSceneClose, [=](){
                this->setGeometry(playScene->geometry());
                this->show();
                delete playScene;
                playScene = NULL;
            });
        });

        //创建按钮中现实的关卡名称
        QLabel * label = new QLabel;
        label->setParent(this);
        label->setFixedSize(levelIcon->width(), levelIcon->height());
        label->setText(QString::number(i+1));
        label->move(25 + (i%4)*70 , 160 + (i/4)*70);
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //设置label上的鼠标事件点击穿透,可以直接触发label下button的信号槽
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent *event)
{
    //绘制背景图
    QPainter qPainter(this);
    QPixmap qPixmap;
    qPixmap.load(":/res/PlayLevelSceneBg.png");
    //绘制背景图
    qPainter.drawPixmap(0,0,this->width(),this->height(),qPixmap);

    //绘制左上角游戏名称
    qPixmap.load(":/res/Title.png");
    qPainter.drawPixmap(20,30,qPixmap.width(),qPixmap.height(),qPixmap);
}
