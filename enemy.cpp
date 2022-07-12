#include "enemy.h"
#include "config.h"
Enemy::Enemy()
{
   m_enemy.load(ENEMYPATH);

   m_X=0;
   m_Y=0;

   m_Free=true;
   m_Speed=1;//敵人初始速度為1，會隨著難度升高加快

   m_Rect.setWidth(m_enemy.width()+5);
   m_Rect.setHeight(m_enemy.height()+5);
   m_Rect.moveTo(m_X,m_Y);
}

void Enemy::updatePisition(){
    if(m_Free){
        return;
    }
    m_X-=m_Speed;
    m_Rect.moveTo(m_X,m_Y);
    if(m_X<=-m_Rect.width()){

        m_Free=true;
    }


}
