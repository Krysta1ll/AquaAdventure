#ifndef HERO_H
#define HERO_H
#include<QPixmap>
#include<QRect>
#include"bullet.h"
#include<QMovie>
#include"config.h"
class Hero
{
public:
    Hero();
    void shoot();
    void stopShoot();
    void setPosition(int x,int y);

public:
   //英雄资源
    QPixmap m_hero;
    QMovie *gif_hero_L=new QMovie(":/new/prefix1/icon/aqua_character.gif");
    QMovie *gif_hero_S=new QMovie(":/new/prefix1/icon/Untitled 07-05-2022 04-14-17.gif");

    //位置坐标
    int m_X;
    int m_Y;
    int speed=0;
    int blood;
    //弹匣
    Bullet m_bullets[BULLET_NUM];

    int m_recorder=0;
    //碰撞体积
    QRect m_Rect;


};

#endif // HERO_H
