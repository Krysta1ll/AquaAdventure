#include "map_scoll.h"

Map_Scoll::Map_Scoll()
{
    m_map1.load(MAP_SCOLL_PATH);
    m_map2.load(MAP_SCOLL_PATH);

    m_map1_X=GAME_WIDTH_FM;//第一張圖片放在屏幕最右側
    m_map2_X=0;//第二張圖片放在屏幕內

    m_scoll_speed=MAP_SCOLL_SPEED;
}

void Map_Scoll::position_Map()
{
   m_map1_X-=MAP_SCOLL_SPEED;  //第一張圖片向左滾動，到達第二張圖片位置時歸位
   if(m_map1_X<=0){
       m_map1_X=GAME_WIDTH_FM;
   }
   m_map2_X-=MAP_SCOLL_SPEED;//第二張圖片向左滾動，完全離開窗口之後歸位
   if(m_map2_X<=-GAME_WIDTH_FM){
       m_map2_X=0;
   }

}
