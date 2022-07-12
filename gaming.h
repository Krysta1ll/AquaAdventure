#ifndef GAMING_H
#define GAMING_H
#include<QTimer>
#include <QWidget>
#include<QPainter>
#include <QFileDialog>
#include "hero.h"
#include"bullet.h"
#include<QKeyEvent>
#include<QLabel>
#include<QPixmap>
#include<iostream>

namespace Ui {
class gaming;
}

class gaming : public QWidget
{
    Q_OBJECT

public:
    explicit gaming(QWidget *parent = nullptr);
    ~gaming();

    void initScene();//初始化游戏
    void gameStart();//开始游戏
//模拟重力
    void gravitySim();
    void bulletUpdatePosition_L();
    void bulletUpdatePosition_R();
    void bulletUpdatePosition_Up();//更新子弹坐标
    void bulletUpdatePosition_Down();

    /*空气墙函数*/
    bool airWall(QRect *a,QRect b);




    //绘制事件
    void paintEvent(QPaintEvent *);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    //地图绘制
    void drawMap();
    void initBullet();
    void initHero();
    //地图导入


    bool initByFile(QString fileName){
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly)){
            return false;
        }

        QByteArray arrAll=file.readAll();
        arrAll.replace("\r\n","\n");
        QList<QByteArray> linelist =arrAll.split('\n');


        mPMap =new int *[40];

        for(int i=0;i<40;i++){
            QList<QByteArray> colList=linelist[i].split(',');
            mPMap[i]=new int[40];
            for(int j=0;j<40;j++){
                mPMap[i][j]=colList[j].toInt();
            }

        }

    }

public:
    QTimer gravity_Timer;
    QTimer m_Timer;
    QTimer bullet_Timer_L;
    QTimer bullet_Timer_Down;
    QTimer bullet_Timer_Up;
    QTimer bullet_Timer_R;
    QPainter m_painter;
    int **mPMap;
    //创建英雄对象
    Hero m_aqua;
    //英雄加入世界
    QLabel *aqua_label=new QLabel(this);
    //键盘输入事件
    QRect walls[1024];
    int wallNum=0;
private:
    Ui::gaming *ui;


};

#endif // GAMING_H
