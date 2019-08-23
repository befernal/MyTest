#include "mypushbutton.h"
#include<QDebug>
#include<QPropertyAnimation>

//MyPushButton::MyPushButton(QWidget *parent) : QWidget(parent)
//{

//}

MyPushButton::MyPushButton(QString normalImg,QString pressImg)
{
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;

    //创建QPixmap对象
    QPixmap pix;
    bool ret = pix.load(this->normalImgPath);

    if(!ret)
    {
        QString str = QString("图标加载失败，错误路径是：%1").arg(this->normalImgPath);
        qDebug() <<str ;
        return;
    }

    //设置固定图片尺寸
    this->setFixedSize(pix.width(),pix.height());

    //设置不规则样式
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    this->setIcon(pix);

    //设置图标的大小
    this->setIconSize(QSize(pix.width(),pix.height()));
}

//向下跳跃
void MyPushButton::zoomDown()
{
    //创建动画对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");

    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置时间间隔
    animation->setDuration(200);

    //设置动画效果
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //开始执行动画
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

//向上跳跃
void MyPushButton::zoomUp()
{
    //创建动画对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");

    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置时间间隔
    animation->setDuration(200);

    //设置动画效果
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //开始执行动画
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

//重写鼠标按下
void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressImgPath!="") //需要切图，换成按下后显示的图片
    {
        QPixmap pix;
        bool ret = pix.load(this->pressImgPath);

        if(!ret)
        {
            QString str = QString("图标加载失败，错误路径是：%1").arg(this->normalImgPath);
            qDebug() <<str ;
            return;
        }

        //设置固定图片尺寸
        this->setFixedSize(pix.width(),pix.height());

        //设置不规则样式
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标
        this->setIcon(pix);

        //设置图标的大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }

    //其余的事件 交给父类处理
    QPushButton::mousePressEvent(e);
}

//重写鼠标释放
void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressImgPath!="") //需要切图，换成按下后显示的图片
    {
        QPixmap pix;
        bool ret = pix.load(this->normalImgPath);

        if(!ret)
        {
            QString str = QString("图标加载失败，错误路径是：%1").arg(this->normalImgPath);
            qDebug() <<str ;
            return;
        }

        //设置固定图片尺寸
        this->setFixedSize(pix.width(),pix.height());

        //设置不规则样式
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标
        this->setIcon(pix);

        //设置图标的大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }

    //其余的事件 交给父类处理
    QPushButton::mouseReleaseEvent(e);
}
