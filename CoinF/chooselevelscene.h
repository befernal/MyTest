#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include"playscene.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = 0);

    //绘图事件
    void paintEvent(QPaintEvent *);

    //维护第三个游戏场景的指针
    PlayScene * playScene;

signals:
    //自定义的信号，返回按钮发送
    void chooseSceneBack();

public slots:
};

#endif // CHOOSELEVELSCENE_H
