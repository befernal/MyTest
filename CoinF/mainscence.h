#ifndef MAINSCENCE_H
#define MAINSCENCE_H

#include <QMainWindow>
#include "chooselevelscene.h"

namespace Ui {
class MainScence;
}

class MainScence : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScence(QWidget *parent = 0);

    //绘图事件
    void paintEvent(QPaintEvent *);


    //维护第二个选择关卡场景的指针
    ChooseLevelScene * chooseScene;

    ~MainScence();

private:
    Ui::MainScence *ui;
};

#endif // MAINSCENCE_H
