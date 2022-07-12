#ifndef MAP_SCOLL_H
#define MAP_SCOLL_H
#include<QPixmap>
#include "config.h"
class Map_Scoll
{
public:
    Map_Scoll();


    void position_Map();

public:
    QPixmap m_map1;
    QPixmap m_map2;

    int m_map1_X;
    int m_map2_X;

    int m_scoll_speed;
};

#endif // MAP_SCOLL_H
