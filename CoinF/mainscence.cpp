#include "mainscence.h"
#include "ui_mainscence.h"
#include<QPainter>
#include"mypushbutton.h"
#include<QDebug>
#include<QTimer>
#include<QSound>

MainScence::MainScence(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScence)
{
    ui->setupUi(this);

    //点击退出 退出游戏
    connect(ui->actionQuit,&QAction::triggered,[=](){
        this->close();
    });

    //设置固定大小
    this->setFixedSize(320,588);

    //设置标题
    this->setWindowTitle("翻金币");

    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //创建第二个选择场景
    this->chooseScene = new ChooseLevelScene;

    //准备开始按钮的点击音效
    QSound * startSound= new QSound(":/res/TapButtonSound.wav",this);

    MyPushButton *startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move((this->width()-startBtn->width())*0.5, this->height() * 0.7);

    //点击按钮相应点击效果
    connect(startBtn,&MyPushButton::clicked,[=](){

        //播放音效
        startSound->play();

        startBtn->zoomDown(); //向下跳跃
        startBtn->zoomUp(); //向上跳跃

        //演示进入到下一个场景
        QTimer::singleShot(500,this,[=](){
            //将自身隐藏掉
            this->hide();

            //设置第二个场景的位置
            this->chooseScene->setGeometry(this->geometry());

            //进入第二个场景
            this->chooseScene->show();
        });
    });

    //监听第二个场景的返回信号
    connect(this->chooseScene,&ChooseLevelScene::chooseSceneBack,[=](){
        this->chooseScene->hide();

        this->setGeometry(this->chooseScene->geometry());

        this->show();
    });

}

//绘图事件
void MainScence::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");

    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");

    //缩放
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);

    painter.drawPixmap(10,30,pix);
}

MainScence::~MainScence()
{
    delete ui;
}
