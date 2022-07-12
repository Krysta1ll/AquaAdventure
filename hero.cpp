#include "hero.h"
#include"config.h"
Hero::Hero()
{
   //初始化
    m_hero.load(HERO_PATH);

    //初始化坐标
    m_X=320;
    m_Y =400;

    //初始化碰撞体积

    m_Rect.setWidth(m_hero.width());
    m_Rect.setHeight(m_hero.height());
    m_Rect.moveTo(m_X,m_Y);

   m_recorder=0;

   blood=100;//初始化血量
}

void Hero::shoot()
{
  m_recorder++;
  if(m_recorder<BULLET_INTERVAL){
      return;
  }
  m_recorder=0;
  for(int i=0;i<BULLET_NUM;i++){
      if(m_bullets[i].m_Free){
          m_bullets[i].m_Free=false;
          m_bullets[i].m_X=m_X+m_Rect.width()*0.5-10;
          m_bullets[i].m_Y=m_Y-25;
          break;
      }
  }

}

//停止射击，暂时未实现的功能
//void Hero::stopShoot()
//{m_recorder++;
//    if(m_recorder<BULLET_INTERVAL){
//        return;
//    }
//    m_recorder=0;
//    for(int i=0;i<BULLET_NUM;i++){
//        if(!m_bullets[i].m_Free){
//            m_bullets[i].m_Free=true;
//            break;
//        }
//    }

//}



void Hero::setPosition(int x, int y)
{
   m_X=x;
   m_Y=y;
   m_Rect.moveTo(m_X,m_Y);


}
