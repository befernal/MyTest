#include "playscene.h"
#include<QDebug>
#include<QMenuBar>
#include"mypushbutton.h"
#include<QPainter>
#include<QTimer>
#include<QLabel>
#include"mycoin.h"
#include "dataconfig.h"
#include<QPropertyAnimation>
#include<QSound>

//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}

PlayScene::PlayScene(int index)
{
    this->levelIndex = index;
    qDebug() << "当前是第"<<this->levelIndex<<"关";

    //设置固定尺寸
    this->setFixedSize(320,588);
    //设置标题
    this->setWindowTitle("翻金币游戏场景");
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //返回按钮音效
    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);
    //翻金币音效
    QSound *flipSound = new QSound(":/res/ConFlipSound.wav",this);
    //胜利按钮音效
    QSound *winSound = new QSound(":/res/LevelWinSound.wav",this);


    //菜单栏
    QMenuBar * mBar = this->menuBar();
    this->setMenuBar(mBar);

    QMenu * startMenu = mBar->addMenu("开始");

    QAction * quitAction = startMenu->addAction("退出");

    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

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

    //显示具体的关卡号
    QLabel * label = new QLabel;
    label->setParent(this);
    QString str = QString("Level:%1").arg(this->levelIndex);
    label->setText( str);
    //设置坐标以及大小
    label->setGeometry(QRect(30,this->height() - 50, this->width(),50 ));
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);
    label->setAttribute(Qt::WA_TransparentForMouseEvents); //51

    //初始化二维数组
    dataConfig config;
    for(int i = 0 ;i < 4;i++)
    {
        for(int j = 0 ;j < 4;j++)
        {

            this->gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }

    //准备胜利的图片
    QLabel * winLable= new QLabel;
    QPixmap pix;
    pix.load(":/res/LevelCompletedDialogBg.png");
    winLable->setGeometry(0,0,pix.width(),pix.height());
    winLable->setPixmap(pix);
    winLable->setParent(this);
    winLable->move( (this->width() - pix.width()) * 0.5, -pix.height());

    //绘制金币的背景图片
    for(int i = 0 ; i< 4;i++)
    {
        for(int j = 0 ;j < 4;j++)
        {

            //金币的背景图
            QLabel *label = new QLabel;
            QPixmap pix;
            pix.load(":/res/BoardNode.png");
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(57+ i*pix.width(),200 +j*pix.height());

            QString str = "";
            if(this->gameArray[i][j] == 1)
            {
                str = ":/res/Coin0001.png";
            }
            else
            {
                str = ":/res/Coin0008.png";
            }

            //创建具体的硬币
            MyCoin * myCoin = new MyCoin(str);
            myCoin->setParent(this);
            myCoin->move(59+ i*pix.width(),204 +j*pix.height());

            //给硬币属性初始化
            myCoin->posX = i;
            myCoin->posY = j;
            myCoin->flag = gameArray[i][j];

            //维护所有硬币指针的数组
            coinBtn[i][j] = myCoin;

            connect(myCoin,&MyCoin::clicked,[=](){

                flipSound->play();

                //点击一个金币，将所有金币点击都禁用
                for(int i = 0 ; i < 4;i++)
                {
                    for(int j = 0;j < 4;j++)
                    {
                        this->coinBtn[i][j]->isWin = true;
                    }
                }

                myCoin->changeFlag();
                //维护二维数组，为了方便以后扩展
                gameArray[i][j] = gameArray[i][j] == 0 ? 1:0;

                QTimer::singleShot(300,this,[=](){
                    //延时翻转周围硬币

                    //翻右侧硬币，检测越界情况
                    if(myCoin->posX + 1 <=3)
                    {
                        coinBtn[myCoin->posX + 1][myCoin->posY]->changeFlag();
                        gameArray[myCoin->posX + 1][myCoin->posY] = gameArray[myCoin->posX + 1][myCoin->posY] == 0 ? 1:0;
                    }
                    //翻转左侧硬币，检测越界情况
                    if(myCoin->posX-1 >=0)
                    {
                        coinBtn[myCoin->posX - 1][myCoin->posY]->changeFlag();
                        gameArray[myCoin->posX - 1][myCoin->posY] = gameArray[myCoin->posX - 1][myCoin->posY] == 0 ? 1:0;
                    }
                    //翻转下侧 检测
                    if(myCoin->posY+1 <= 3)
                    {
                        coinBtn[myCoin->posX][myCoin->posY+1]->changeFlag();
                        gameArray[myCoin->posX][myCoin->posY+1] = gameArray[myCoin->posX][myCoin->posY+1] == 0 ? 1:0;
                    }
                    //翻转上侧 检测
                    if(myCoin->posY-1 >= 0)
                    {
                        coinBtn[myCoin->posX][myCoin->posY-1]->changeFlag();
                        gameArray[myCoin->posX][myCoin->posY-1] = gameArray[myCoin->posX][myCoin->posY-1] == 0 ? 1:0;
                    }

                    //胜利的检测
                    this->isWin = true;
                    for(int i = 0 ;i < 4;i++)
                    {
                        for(int j = 0 ; j < 4;j++)
                        {
                              if(coinBtn[i][j]->flag == false)
                              {
                                  this->isWin = false; //游戏未胜利
                                  break;
                              }

                        }
                    }

                    if(this->isWin)
                    {
                        qDebug() << "游戏胜利";
                        winSound->play();

                        for(int i = 0 ; i < 4;i++)
                        {
                            for(int j = 0;j < 4;j++)
                            {
                                this->coinBtn[i][j]->isWin = true;
                            }
                        }

                        //将胜利图片显示
                        QPropertyAnimation * animation = new QPropertyAnimation(winLable,"geometry");
                        animation->setStartValue(QRect(winLable->x(),winLable->y(),winLable->width(),winLable->height()));
                        animation->setEndValue(QRect(winLable->x(),winLable->y() + 190,winLable->width(),winLable->height()) );
                        animation->setDuration(1000);
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start(QAbstractAnimation::DeleteWhenStopped);

                    }
                    else
                    {
                        //未胜利，开始所有金币点击事件
                        for(int i = 0 ; i < 4;i++)
                        {
                            for(int j = 0;j < 4;j++)
                            {
                                this->coinBtn[i][j]->isWin = false;
                            }
                        }

                    }
                });
            });

        }
    }
}

//重写绘图事件
void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");

    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap( 10,30,pix.width(),pix.height(),pix);

}
