#include "gaming.h"
#include "ui_gaming.h"
#include"config.h"
#include<QTimer>
#include<QPixmap>
#include"pause.h"






gaming::gaming(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gaming)
{
    ui->setupUi(this);


    initScene(); //初始化场景

    gameStart(); //开始游戏

}







gaming::~gaming()
{
    delete ui;
}









//这里是启动游戏之后必要的初始化内容

void gaming::initScene()
{      QPixmap backGround(":/new/prefix1/icon/backGround.png");


       QString fileName=QFileDialog::getOpenFileName(this,"打开地图","./","*.txt");//导入地图文件浏览器


          initByFile(fileName);  //导入地图
             this->setWindowTitle("gaming");                                      //规定了窗口名
             this->setFixedSize(GAME_WIDTH_FM,GAME_HEIGHT_FM);                          //窗口的大小


             m_Timer.setInterval(1);                                   //主定时器
                bullet_Timer_L.setInterval(BULLET_INTERVAL);                       //子弹左射定时器
                   bullet_Timer_R.setInterval(BULLET_INTERVAL);                       //子弹右射定时器
                      bullet_Timer_Up.setInterval(BULLET_INTERVAL);                      //子弹上射定时器

                            bullet_Timer_Down.setInterval(BULLET_INTERVAL);
}









//这里是设置游戏启动后通过计时器发出的信号函数
//必须加载

void gaming::gameStart(){
    m_Timer.start();

    connect(&m_Timer,&QTimer::timeout,[=](){               //主计时器，用于更新画面

        update();//重新绘制
    });
    connect(&bullet_Timer_Up,&QTimer::timeout,[=](){
        bulletUpdatePosition_Up();//更新子弹坐标
    });
    connect(&bullet_Timer_L,&QTimer::timeout,[=](){
        bulletUpdatePosition_L();//更新子弹坐标
    });
    connect(&bullet_Timer_R,&QTimer::timeout,[=](){
        bulletUpdatePosition_R();//更新子弹坐标
    });
    connect(&bullet_Timer_Down,&QTimer::timeout,[=](){
        bulletUpdatePosition_Down();//更新子弹坐标
    });


}











void gaming::bulletUpdatePosition_Up(){
   m_aqua.shoot();
    for(int i=0;i<BULLET_NUM;i++){
        if(!m_aqua.m_bullets[i].m_Free){
            m_aqua.m_bullets[i].updPosition_Up();
        }
    }

}

void gaming::bulletUpdatePosition_Down()
{
    m_aqua.shoot();
     for(int i=0;i<BULLET_NUM;i++){
         if(!m_aqua.m_bullets[i].m_Free){
             m_aqua.m_bullets[i].updPosition_Down();
         }
     }

}

void gaming::bulletUpdatePosition_L(){
   m_aqua.shoot();
    for(int i=0;i<BULLET_NUM;i++){
        if(!m_aqua.m_bullets[i].m_Free){
            m_aqua.m_bullets[i].updPosition_L();
        }
    }

}
void gaming::bulletUpdatePosition_R(){
   m_aqua.shoot();
    for(int i=0;i<BULLET_NUM;i++){
        if(!m_aqua.m_bullets[i].m_Free){
            m_aqua.m_bullets[i].updPosition_R();
        }
    }

}







//下方为判断空气墙函数
bool gaming::airWall(QRect *a,QRect b)
{
    for(int i=0;i<wallNum;i++){
        if(a[i].intersects(b)){
            return true;
        }
    }
    return false;
}







//繪製遊戲地圖,英雄
void gaming::paintEvent(QPaintEvent *){


m_painter.begin(this);

    drawMap();  //绘制地图
    initBullet();

    initHero();
m_painter.end();


}






//绘制地图的函数
void gaming::drawMap()
{

    QPixmap wall;          //定义墙壁地图元素 
    wall.load(":/new/prefix1/icon/groundTest.png");

    QPixmap land;
    land.load(":/new/prefix2/icon/land.png");

    QPixmap grass;
    grass.load(":/new/prefix2/icon/land-Grass.png");

    QPixmap water;
    water.load(":/new/prefix2/icon/Water.png");

    QPixmap river_side;
    river_side.load(":/new/prefix2/icon/River_side_r.png");

    QPixmap grass_land;
    grass_land.load(":/new/prefix2/icon/Grass.png");

    QPixmap grass_edge;
    grass_edge.load(":/new/prefix2/icon/grass_edge.png");

    for(int i=0;i<40;i++){
        for(int j=0;j<40;j++){

                        if(mPMap[i][j]==0){
                            m_painter.drawPixmap(i*20,j*15,20,15,land);  //绘制地图中的元素，墙壁

                        }


            if(mPMap[i][j]==1){
               walls[wallNum].setRect(i*20,j*15,20,15);
               wallNum++;
                m_painter.drawPixmap(i*20,j*15,20,15,wall);  //绘制地图中的元素，

            }
            if(mPMap[i][j]==2){
                m_painter.drawPixmap(i*20,j*15,20,15,grass);  //绘制地图中的元素，

            }
            if(mPMap[i][j]==3){
                m_painter.drawPixmap(i*20,j*15,20,15,grass_land);  //绘制地图中的元素，

            }
            if(mPMap[i][j]==4){
                m_painter.drawPixmap(i*20,j*15,20,15,water);  //绘制地图中的元素，

            }
            if(mPMap[i][j]==5){
                walls[wallNum].setRect(i*20,j*15,20,15);
                wallNum++;
                m_painter.drawPixmap(i*20,j*15,20,15,river_side);  //绘制地图中的元素，墙壁

            }
            if(mPMap[i][j]==6){
                m_painter.drawPixmap(i*20,j*15,20,15,grass_edge);  //绘制地图中的元素，墙壁

            }



        }
    }

}







//绘制英雄的函数
void gaming::initHero()
{
  m_painter.drawPixmap(m_aqua.m_X,m_aqua.m_Y,m_aqua.m_hero);



//     aqua_label->setGeometry(m_aqua.m_X,m_aqua.m_Y,40,30);
//     m_aqua.gif_hero_S->start();
//     aqua_label->setMovie(m_aqua.gif_hero_S);

}


void gaming::initBullet()
{
    for(int i=0;i<BULLET_NUM;i++)
    {
        if(!m_aqua.m_bullets[i].m_Free){
            m_painter.drawPixmap(m_aqua.m_bullets[i].m_X,m_aqua.m_bullets[i].m_Y,20,20,m_aqua.m_bullets->m_bullet);

            //子弹的另一种实现方法
            /*aqua_bullet->setGeometry(m_aqua.m_bullets[i].m_X,m_aqua.m_bullets[i].m_Y,20,10);
            aqua_bullet->setPixmap(m_aqua.m_bullets[i].m_bullet);
            aqua_bullet->show();*/
        }
    }

}







/*目前该函数存在一些问题
 * ##1需要添加其他方向的子弹射击---完成但需要改进
 *
 *
 *
 * 控制英雄的移动,射击*/
void gaming::keyPressEvent(QKeyEvent *event)
{

    //这里是左键移动
    if(event->key()==Qt::Key_A||event->key()==Qt::Key_Left){


        /* 如果按下移动键之后，角色碰撞到空气墙，将会把角色逆向反弹
           下方代码同理*/


        if(airWall(walls,m_aqua.m_Rect)){
            m_aqua.m_X+=16;
            m_aqua.setPosition(m_aqua.m_X,m_aqua.m_Y);
            update();
            return;
        }else{
            m_aqua.m_X-=15;
            m_aqua.setPosition(m_aqua.m_X,m_aqua.m_Y);

        }

    }

    //这里是右键移动
    if(event->key()==Qt::Key_D||event->key()==Qt::Key_Right){

        if(airWall(walls,m_aqua.m_Rect)){
            m_aqua.m_X-=16;
            m_aqua.setPosition(m_aqua.m_X,m_aqua.m_Y);

            return;
        }
//        m_aqua.speed++;
//        m_aqua.m_X+=m_aqua.speed;
        m_aqua.m_X+=15;
        m_aqua.setPosition(m_aqua.m_X,m_aqua.m_Y);


    }

    if(event->key()==Qt::Key_W||event->key()==Qt::Key_Up){
        if(airWall(walls,m_aqua.m_Rect)){

            m_aqua.m_Y+=16;
            m_aqua.setPosition(m_aqua.m_X,m_aqua.m_Y);

            return;
        }
        m_aqua.m_Y-=15;
        m_aqua.setPosition(m_aqua.m_X,m_aqua.m_Y);

    }

    if(event->key()==Qt::Key_S||event->key()==Qt::Key_Down){
        if(airWall(walls,m_aqua.m_Rect)){
            m_aqua.m_Y-=16;
            m_aqua.setPosition(m_aqua.m_X,m_aqua.m_Y);

            return;
        }
        m_aqua.m_Y+=15;
        m_aqua.setPosition(m_aqua.m_X,m_aqua.m_Y);

    }




    //开始射击
    if(event->key()==Qt::Key_G){
        bullet_Timer_L.start();
    }

    if(event->key()==Qt::Key_Y){
        bullet_Timer_Up.start();
    }
    if(event->key()==Qt::Key_J){
        bullet_Timer_R.start();
    }
    if(event->key()==Qt::Key_H){
        bullet_Timer_Down.start();
    }



    if(event->key()==Qt::Key_Escape){


    }

}









//松开开火键之后停火
void gaming::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_G||event->key()==Qt::Key_Y||event->key()==Qt::Key_J||event->key()==Qt::Key_H){
        bullet_Timer_L.stop();
        bullet_Timer_R.stop();
        bullet_Timer_Up.stop();
        bullet_Timer_Down.stop();
        for(int i=0;i<BULLET_NUM;i++){
            m_aqua.m_bullets[i].m_Free=true;
        }
        update();
    }

//    if(event->key()==Qt::Key_D){
//        if(m_aqua.speed>0){
//        m_aqua.speed--;
//        m_aqua.m_X+=m_aqua.speed;
//        update();}else if(m_aqua.speed==0)return;
//    }
}



