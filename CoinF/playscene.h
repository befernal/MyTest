#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include"mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = 0);

    PlayScene(int index);

    int levelIndex; //当前关卡号

    //重写绘图事件
    void paintEvent(QPaintEvent *);

    //设计二维数组，维护当前关卡的金币和银币的显示
    int gameArray[4][4];

    //设计二维数组，维护硬币
    MyCoin* coinBtn[4][4];

    //判断胜利的标志
    bool isWin = true;

signals:
    void chooseSceneBack();

public slots:
};

#endif // PLAYSCENE_H
