#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include<QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = 0);

    MyCoin(QString btnImg);

    int posX; //x坐标
    int posY; //y坐标
    bool flag; //正反标志

    //翻转金币的功能
    void changeFlag();

    //定时器
    QTimer * timer1; //金币翻银币定时器
    QTimer * timer2; //银币翻金币定时器

    //图标下标
    int min = 1; //最小值下标
    int max = 8; //最大值下标

    //硬币是否正在做动画的标志
    bool isAnimation = false;

    //重新鼠标按下事件
    void mousePressEvent(QMouseEvent *e);

    //每个金币也加属性，判断是否胜利
    bool isWin = false;

signals:

public slots:
};

#endif // MYCOIN_H
