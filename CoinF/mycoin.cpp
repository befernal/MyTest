#include "mycoin.h"
#include<QDebug>

//MyCoin::MyCoin(QWidget *parent) : QWidget(parent)
//{

//}

MyCoin::MyCoin(QString btnImg)
{
    QPixmap pix;
    bool ret = pix.load(btnImg);
    if(!ret)
    {
        QString str = QString("图片加载失败，失败路径：%1").arg(btnImg);
        qDebug() <<str;
        return;
    }

    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    //定时器创建
    this->timer1 = new QTimer(this);
    this->timer2 = new QTimer(this);

    //监听定时器信号
    connect(timer1,&QTimer::timeout,[=](){

        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->min++);
        bool ret = pix.load(str);
        if(!ret)
        {
            QString str = QString("图片加载失败，失败路径：%1").arg(btnImg);
            qDebug() <<str;
            return;
        }

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        if(this->min > this->max)
        {
            this->timer1->stop();
            this->min = 1;
            isAnimation = false;
        }

    });


    //银币翻金币定时器监听
    connect(timer2,&QTimer::timeout,[=](){

        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->max--);
        bool ret = pix.load(str);
        if(!ret)
        {
            QString str = QString("图片加载失败，失败路径：%1").arg(btnImg);
            qDebug() <<str;
            return;
        }

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        if(this->max < this->min)
        {
            this->timer2->stop();
            this->max = 8;
            isAnimation = false;
        }

    });


}


//翻转金币的功能
void MyCoin::changeFlag()
{
    if(this->flag)
    {
        //将标志改为银币
        this->flag = false;
        //启动金币翻银币的定时器
        timer1->start(30);
    }
    else
    {
        //将标志改为金币
        this->flag = true;
        //启动银币翻金币的定时器
        timer2->start(30);
    }

    //正在做动画，将标志置为true
    isAnimation = true;
}

//重新鼠标按下事件
void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation | this->isWin)
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
}
