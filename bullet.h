#ifndef BULLET_H
#define BULLET_H
#include<QPixmap>
#include<QRect>
#include"config.h"
class Bullet
{
public:
    Bullet();

    void updPosition_Up();
    void updPosition_L();
    void updPosition_R();
    void updPosition_Down();

public:
    QPixmap m_bullet;
    int m_X;
    int m_Y;
    int m_Speed;
    bool m_Free;
    QRect m_Rect;

};

#endif // BULLET_H
