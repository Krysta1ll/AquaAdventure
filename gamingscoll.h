#ifndef GAMINGSCOLL_H
#define GAMINGSCOLL_H

#include <QWidget>
#include<QTimer>
#include<QPainter>
#include"map_scoll.h"
#include<QKeyEvent>
#include"hero.h"
#include<QLabel>
#include"enemy.h"
#include"bullet.h"
#include<QMediaPlayer>
#include<QMediaPlaylist>
namespace Ui {
class gamingScoll;
}

class gamingScoll : public QWidget
{
    Q_OBJECT

public:
    explicit gamingScoll(QWidget *parent = nullptr);
    ~gamingScoll();
    void initScene();    //初始化函數

    void gameStart();     //控制遊戲開始函數

    void updatePosition();      //刷新位置

    void paintEvent(QPaintEvent *);   //繪圖事件

    void keyPressEvent(QKeyEvent *event);   //按鍵事件

    void initHero();       //初始化玩家

    void bulletUpdatePosition_R();  //向右開火函數

    void initBullet();          //初始化子彈

    void collisionBox();    //碰撞箱檢測
    /*空气墙函数*/
    void keyReleaseEvent(QKeyEvent *event);    //用於按鍵開火

    void initEnemy();     //初始化敵人

    void health_Dect();//生命值檢測

    void level_Set();

    Enemy m_enemys[ENEMY_NUM];

    int m_recorder=0;



public:
    QTimer m_Timer;
    Map_Scoll m_map;
    bool is_paused=false;
    Hero m_aqua;
    QLabel *aqua_label=new QLabel(this);
    QTimer bullet_Timer_R;
    QPainter m_painter;//畫筆
    int score=0;//關卡分數
    int level=1;//當前關卡等級
    int superSpeed=1;//超級敵人的速度
    //遊戲bgm
    QMediaPlayer *bgm=new QMediaPlayer(this);
    QMediaPlaylist *playlist=new QMediaPlaylist(this);


private slots:

    void on_exit_clicked();

    void on_continue_button_clicked();

private:
    Ui::gamingScoll *ui;
};

#endif // GAMINGSCOLL_H
