#ifndef CONFIG_H
#define CONFIG_H

#define GAME_WIDTH_FM 800
#define GAME_HEIGHT_FM 600

#define MAP_SCOLL_PATH ":/new/prefix1/icon/background (1).png"
#define MAP_SCOLL_SPEED 2

#define GAME_TIMER 5

#define HERO_PATH ":/new/prefix2/icon/m_Untitled 07-05-2022 04-14-17.png"
#define HERO_X 40
#define HERO_Y 520
#define BULLET_PATH ":/new/prefix1/icon/bullet.png"
#define BULLET_SPEED 5    //子彈速度，（注意相對速度）
#define BULLET_NUM 30       //子彈個數
#define BULLET_INTERVAL 20



#define ENEMYPATH ":/new/prefix2/icon/Elf_Copter.png"
#define ENEMY_SPEED 1
#define ENEMY_NUM 20       //同時可出現的最大敵人數目
#define ENEMY_INTERVAL 30   //可以在這裡控制敵人刷新的頻率
//地图元素
#define WALL ":/new/prefix1/icon/groundTest.png"

#endif // CONFIG_H
