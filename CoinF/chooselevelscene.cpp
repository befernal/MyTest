#include "chooselevelscene.h"
#include<QPainter>
#include<QMenuBar>
#include"mypushbutton.h"
#include<QTimer>
#include<QLabel>
#include<QDebug>
#include<QSound>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //设置固定尺寸
    this->setFixedSize(320,588);
    //设置标题
    this->setWindowTitle("选择关卡");
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //菜单栏
    QMenuBar * mBar = this->menuBar();
    this->setMenuBar(mBar);

    QMenu * startMenu = mBar->addMenu("开始");

    QAction * quitAction = startMenu->addAction("退出");

    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //准备点击关卡音效
    QSound *chooseSound = new QSound(":/res/TapButtonSound.wav",this);
    //返回按钮音效
    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);

    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()- backBtn->width() , this->height() - backBtn->height());

    //点击返回按钮，发送信号
    connect(backBtn,&MyPushButton::clicked,[=](){

        backSound->play();

        QTimer::singleShot(500,this,[=](){
            //延时发送返回信号
             emit this->chooseSceneBack();
        });
    });


    playScene = NULL; //第三个场景指针

    //创建关卡按钮
    for(int i = 0 ; i < 20 ; i++)
    {
        MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25 + (i%4)*70 , 140+ (i/4)*70);

        //点击按钮 进入到具体游戏关卡
        connect(menuBtn,&MyPushButton::clicked,[=](){
               //qDebug() << "您选择的是第"<< i+1 <<"关";

            chooseSound->play();

            //创建对应的游戏场景
            if(this->playScene == NULL)
            {
                this->playScene = new PlayScene(i+1);

                this->hide();

                this->playScene->setGeometry(this->geometry());

                this->playScene->show();

                connect(this->playScene,&PlayScene::chooseSceneBack,[=](){
                        this->playScene->hide();

                        this->setGeometry(this->playScene->geometry());

                        this->show();

                        delete this->playScene;
                        this->playScene = NULL;
                });
            }
        });

        //按钮上显示的文字
        QLabel * label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter); //设置居中
        label->move(25 + (i%4)*70 , 140+ (i/4)*70);
        label->setAttribute(Qt::WA_TransparentForMouseEvents,true);  //鼠标事件穿透




    }

}

//绘图事件
void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

     //加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap( (this->width() - pix.width())*0.5,30,pix.width(),pix.height(),pix);

}
