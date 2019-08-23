#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = 0);

    MyPushButton(QString normalImg,QString pressImg = "");

    //利用成员属性 记录这两个路径
    QString normalImgPath;
    QString pressImgPath;

    //向上跳跃
    void zoomUp();

    //向下跳跃
    void zoomDown();

    //重写鼠标按下
    void mousePressEvent(QMouseEvent *e);
    //重写鼠标释放
    void mouseReleaseEvent(QMouseEvent *e);

signals:

public slots:
};

#endif // MYPUSHBUTTON_H
