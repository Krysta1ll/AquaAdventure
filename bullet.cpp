#include "bullet.h"
#include"config.h"
Bullet::Bullet()
{
   m_bullet.load(BULLET_PATH);//加载资源
    m_X=HERO_X;
   m_Y=HERO_Y;
   m_Free=true;
   m_Speed=BULLET_SPEED;
   m_Rect.setWidth(5);//m_bullet.width());
   m_Rect.setHeight(5);//m_bullet.height());
   m_Rect.moveTo(m_X,m_Y);
}

void Bullet::updPosition_Up()
{   //未激发时的子弹
    if(m_Free){
        return;
    }
    m_Y-=m_Speed;  //向上飛座標減小
    m_Rect.moveTo(m_X,m_Y);
//飛出遊戲區域之後，子彈變為空閒狀態
    if(m_Y<=-m_Rect.height()){
        m_Free=true;
    }
}

void Bullet::updPosition_Down()
{   //未激发时的子弹
    if(m_Free){
        return;
    }
    m_Y+=m_Speed;
    m_Rect.moveTo(m_X,m_Y);
//飛出遊戲區域之後，子彈變為空閒狀態
    if(m_Y>=GAME_HEIGHT_FM+m_Rect.height()){
        m_Free=true;
    }
}



void Bullet::updPosition_L()
{
    //未激发时的子弹
        if(m_Free){
            return;
        }
        m_X-=m_Speed;
        m_Rect.moveTo(m_X,m_Y);

        if(m_X<=-m_Rect.width()){
            m_Free=true;
        }
}

void Bullet::updPosition_R()
{
    //未激发时的子弹
        if(m_Free){
            return;
        }
        m_X+=m_Speed;
        m_Rect.moveTo(m_X,m_Y);

        if(m_X>=GAME_WIDTH_FM+m_Rect.width()){
            m_Free=true;
        }
}
