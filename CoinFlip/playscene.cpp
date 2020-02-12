#include "playscene.h"

#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QDebug>
#include <QSound>
#include <QPropertyAnimation>

#include "mypushbutton.h"
#include "mycoin.h"
#include "dataconfig.h"

PlayScene::PlayScene(int levelNum)
{
    this->levelIndex = levelNum;
    //设置窗体的属性
    //设置固定大小
    setFixedSize(320, 588);

    //设置应用图标
    setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //设置窗口标题
    setWindowTitle("翻金币场景");

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
            emit this->playSceneClose();
        });
    });

    //设置关卡显示在左下角
    QLabel * label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("宋体");
    font.setPointSize(24);
    label->setFont(font);
    QString str = QString("Leavel: %1").arg(this->levelIndex);
    label->setText(str);
    label->setGeometry(QRect(30, this->height() - 60,120, 50));

    //根据传入的关卡名称,初始化关卡游戏信息
    dataConfig config;
    gameData = config.mData[levelIndex];

    //展示金币的背景
    for (int i = 0 ;i < 4; i++)
    {
        for (int j = 0 ;j < 4; j++)
        {
            QLabel * label = new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/res/BoardNode(1).png"));
            label->setParent(this);
            label->move(57 + i*50,200+j*50);

            //根据关卡数据设置金币的正反面
            QString img;
            if(gameData[i][j] == 1)
            {
                img = ":/res/Coin0001.png";
            }else {
                img = ":/res/Coin0008.png";
            }

            //创建金币
            MyCoin * coin = new MyCoin(img);
            coin->setParent(this);
            coin->posX = i;
            coin->posY = j;
            coin->flag = gameData[i][j];    //  本身保存1和0
            coin->move(59 + i*50,203+j*50);

            //把每个创建出来的金币对象放入二维数组中
            this->myCoin[i][j] = coin;

            //游戏胜利的提示图片
            QLabel * successLabel = new QLabel;
            QPixmap qPixmap;
            qPixmap.load(":/res/LevelCompletedDialogBg.png");
            successLabel->setGeometry(0,0,qPixmap.width(), qPixmap.height());
            successLabel->setPixmap(qPixmap);
            successLabel->setParent(this);
            successLabel->move((this->width() - qPixmap.width())*0.5 , -qPixmap.height());

            //翻金币音效
            QSound *flipSound = new QSound(":/res/ConFlipSound.wav",this);
            //胜利按钮音效
            QSound *winSound = new QSound(":/res/LevelWinSound.wav",this);

            //监听每个金币按钮的点击特效
            connect(coin, &MyCoin::clicked, [=](){
                flipSound->play();

                coin->changeFlag();
                //数组内关卡数据同步修改
                gameData[i][j] = gameData[i][j] == 0 ? 1 : 0;

                //延时翻动周围的金币
                QTimer::singleShot(300, this, [=](){
                    if(coin->posX+1 <=3)
                    {
                        myCoin[coin->posX+1][coin->posY]->changeFlag();
                        gameData[coin->posX+1][coin->posY] = gameData[coin->posX+1][coin->posY]== 0 ? 1 : 0;
                    }
                    if(coin->posX-1>=0)
                    {
                        myCoin[coin->posX-1][coin->posY]->changeFlag();
                        gameData[coin->posX-1][coin->posY] = gameData[coin->posX-1][coin->posY]== 0 ? 1 : 0;
                    }
                    if(coin->posY+1<=3)
                    {
                        myCoin[coin->posX][coin->posY+1]->changeFlag();
                        gameData[coin->posX][coin->posY+1] = gameData[coin->posX][coin->posY+1]== 0 ? 1 : 0;
                    }
                    if(coin->posY-1>=0)
                    {
                        myCoin[coin->posX][coin->posY-1]->changeFlag();
                        gameData[coin->posX][coin->posY-1] = gameData[coin->posX][coin->posY-1]== 0 ? 1 : 0;
                    }

                    //判断是否胜利
                    this->winFlag = true;
                    for (int i = 0 ; i < 4 ; i++)
                    {
                        for (int j = 0 ; j < 4 ; j++)
                        {
                            if(gameData[i][j] == 0)
                            {
                                this->winFlag = false;
                                break;
                            }
                        }
                    }

                    if(this->winFlag)
                    {
                        winSound->play();
                        //金币设置全部为成功标示,用来禁用成功后的点击事件
                        for (int i = 0 ; i < 4 ; i++)
                        {
                            for (int j = 0 ; j < 4 ; j++)
                            {
                                myCoin[i][j]->winFlag = true;
                            }
                        }

                        QPropertyAnimation * animation1 =  new QPropertyAnimation(successLabel,"geometry");
                        animation1->setDuration(1000);
                        animation1->setStartValue(QRect(successLabel->x(),successLabel->y(),successLabel->width(),successLabel->height()));
                        animation1->setEndValue(QRect(successLabel->x(),successLabel->y()+114,successLabel->width(),successLabel->height()));
                        animation1->setEasingCurve(QEasingCurve::OutBounce);
                        animation1->start();
                    }
                });
            });
        }
    }
}

//重写画家
void PlayScene::paintEvent(QPaintEvent *event)
{
    //创建画家
    QPainter qPainter(this);
    //创建绘图
    QPixmap qPixmap;

    qPixmap.load(":/res/OtherSceneBg.png");
    //绘制背景图
    qPainter.drawPixmap(0,0,this->width(),this->height(),qPixmap);

    //绘制左上角游戏名称
    qPixmap.load(":/res/Title.png");
    //缩放一倍
    qPixmap = qPixmap.scaled(qPixmap.width() * 0.5, qPixmap.height() * 0.5);
    qPainter.drawPixmap(10,30,qPixmap.width(),qPixmap.height(),qPixmap);

}
