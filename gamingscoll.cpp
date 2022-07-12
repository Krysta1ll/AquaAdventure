#include "gamingscoll.h"
#include "ui_gamingscoll.h"
#include"config.h"
#include "hero.h"
#include <ctime>
gamingScoll::gamingScoll(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gamingScoll)
{
    ui->setupUi(this);
    initScene();//初始化窗口
    ui->widget->show(); //開始菜單欄

}

gamingScoll::~gamingScoll()
{
    delete ui;
}







/*
--------------------------------------------------------------


這裡是遊戲的初始化函數，決定了能否正常打開遊戲介面


--------------------------------------------------------------
*/
void gamingScoll::initScene(){
    ui->pause->hide();  //暫停介面隱藏
    ui->gameOver->hide();  //遊戲失敗介面隱藏

    //設置循環播放
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    QString bgmurl="/Users/wangtianyu/AquaAdventure2/audio/Scollbgm.mp3";
    playlist->addMedia(QUrl::fromLocalFile(bgmurl));
    bgm->setPlaylist(playlist);
    bgm->setVolume(50);



    setFixedSize(GAME_WIDTH_FM,GAME_HEIGHT_FM);
    setWindowTitle("阿夸大冒險");
    m_Timer.setInterval(10);                       //這裡是遊戲主計時器
//    bullet_Timer_R.setInterval(BULLET_INTERVAL);   //這裡是另一種開火方式，按鍵開火，但存在許多bug
    srand((unsigned int)time(NULL));               //隨即刷新敵人的隨機數種子

}






/*
--------------------------------------------------------------


這裡是遊戲的開始函數


--------------------------------------------------------------
*/
void gamingScoll::gameStart(){
 bgm->play();
    m_Timer.start();
    //刷新遊戲中的元素
    connect(&m_Timer,&QTimer::timeout,[=](){
        if(!is_paused){
            initEnemy();   //刷新敵人
            updatePosition();//刷新子彈位置
            update();
            collisionBox();   //檢測碰撞
            health_Dect();//生命值檢測
            level_Set();  //關卡設置
            ui->lcdNumber->display(score);//計分板
            ui->healthBar->setValue(m_aqua.blood);//血條
            ui->level->display(level);
        }});



    //    connect(&bullet_Timer_R,&QTimer::timeout,[=](){
    //        bulletUpdatePosition_R();//更新子弹坐标
    //    });

}










//刷新遊戲內元素
void gamingScoll::updatePosition(){
    m_map.position_Map();

    //生成敵人
    for(int i=0;i<ENEMY_NUM;i++){
        if(m_enemys[i].m_Free==false){
            m_enemys[i].updatePisition();
        }
    }

    bulletUpdatePosition_R();


}





//初始化玩家
void gamingScoll::initHero(){

    //    m_painter.drawPixmap(m_aqua.m_X,m_aqua.m_Y,m_aqua.m_hero);

    aqua_label->setGeometry(m_aqua.m_X,m_aqua.m_Y,126,108);
    aqua_label->setMovie(m_aqua.gif_hero_L);
    aqua_label->show();
    m_aqua.gif_hero_L->start();

}




//初始化子彈
void gamingScoll::initBullet()
{
    for(int i=0;i<BULLET_NUM;i++)
    {
        if(!m_aqua.m_bullets[i].m_Free){
            m_painter.drawPixmap(m_aqua.m_bullets[i].m_X,m_aqua.m_bullets[i].m_Y,20,20,m_aqua.m_bullets->m_bullet);
        }
    }
}



//初始化敵人
void gamingScoll::initEnemy()
{
    m_recorder++;
    if(m_recorder<ENEMY_INTERVAL){
        return;
    }
    m_recorder=0;
    for(int i=0;i<ENEMY_NUM;i++){
        if(m_enemys[i].m_Free){
            m_enemys[i].m_Free=false;
            m_enemys[i].m_Y=rand()%(GAME_HEIGHT_FM-m_enemys[i].m_Rect.height());
                    m_enemys[i].m_X=GAME_WIDTH_FM+m_enemys[i].m_Rect.width();
            break;
        }

    }
}



void gamingScoll::health_Dect()
{
//首先判斷，若是敵人通過最左邊安全區時，扣除玩家血量
    for(int i=0;i<ENEMY_NUM;i++){
        if(m_enemys[i].m_X==1){
            m_aqua.blood-=5;
            if(m_aqua.blood<0)m_aqua.blood=0;
        }
    }
    if(m_aqua.blood==0){
        ui->gameOver->show();
        m_Timer.stop();
        bgm->stop();
        m_aqua.setPosition(1000,1000);
        update();
        ui->last_score->display(score);

    }


}

void gamingScoll::level_Set()
{

    if(score==level*100) {
        level++;

        for(int i=0;i<level;i++){
            if(i<2){
                superSpeed++;   //超級敵人最快速度為2

            }
            m_enemys[i].m_Speed=superSpeed;  //增加超級敵人數量
            m_enemys[i].updatePisition();
        }

    }
}





void gamingScoll::collisionBox()//碰撞箱檢測
{
    for(int i=0;i<ENEMY_NUM;i++){
        if(m_enemys[i].m_Free){
            continue;//死亡或者未刷新的敵人不進行檢測
        }
        for(int j=0;j<BULLET_NUM;j++){
            if(m_aqua.m_bullets[j].m_Free) {
                continue;
            }
            if(m_enemys[i].m_Rect.intersects(m_aqua.m_bullets[j].m_Rect))//當子彈擊中敵人時，敵人死亡，分數+1

            {
                m_enemys[i].m_Free=true;
                m_aqua.m_bullets[j].m_Free=true;
                score++;
            }else if(m_enemys[i].m_Rect.intersects(m_aqua.m_Rect)){//當玩家與敵人相撞，扣除5點血量
                 m_enemys[i].m_Free=true;
                 m_aqua.blood-=5*level;
            }
        }

    }

}

//刷新子彈位置
void gamingScoll::bulletUpdatePosition_R(){
    m_aqua.shoot();
    for(int i=0;i<BULLET_NUM;i++){
        if(!m_aqua.m_bullets[i].m_Free){
            m_aqua.m_bullets[i].updPosition_R();
        }
    }

}





//繪圖事件
void gamingScoll::paintEvent(QPaintEvent *){

    m_painter.begin(this);

    m_painter.drawPixmap(m_map.m_map1_X,0,m_map.m_map1);
    m_painter.drawPixmap(m_map.m_map2_X,0,m_map.m_map2);
    initBullet();
    initHero();
    //enemy
    for (int i=0;i<ENEMY_NUM;i++) {
        if(m_enemys[i].m_Free==false){
            m_painter.drawPixmap(m_enemys[i].m_X,m_enemys[i].m_Y,m_enemys[i].m_enemy);
        }

    }
    m_painter.end();
}






void gamingScoll::keyPressEvent(QKeyEvent *event)   //鍵盤事件判斷
{
    if(event->key()==Qt::Key_Escape){   //esc打開暫停介面
        ui->pause->show();
        is_paused=true;

    }

    //这里是左键移动
    if(event->key()==Qt::Key_A||event->key()==Qt::Key_Left){

        m_aqua.m_X-=25;
        m_aqua.setPosition(m_aqua.m_X,m_aqua.m_Y);

    }

    //这里是右键移动
    if(event->key()==Qt::Key_D||event->key()==Qt::Key_Right){

        m_aqua.m_X+=25;
        m_aqua.setPosition(m_aqua.m_X,m_aqua.m_Y);


    }

    if(event->key()==Qt::Key_W||event->key()==Qt::Key_Up){

        m_aqua.m_Y-=25;
        m_aqua.setPosition(m_aqua.m_X,m_aqua.m_Y);

    }

    if(event->key()==Qt::Key_S||event->key()==Qt::Key_Down){
        if(m_aqua.m_Y!=600){
            m_aqua.m_Y+=25;
            m_aqua.setPosition(m_aqua.m_X,m_aqua.m_Y);
        }


    }
//    if(event->key()==Qt::Key_G){
//        bullet_Timer_R.start();

//    }

}

void gamingScoll::keyReleaseEvent(QKeyEvent *event)
{
//    if(event->key()==Qt::Key_G||event->key()==Qt::Key_Y||event->key()==Qt::Key_J||event->key()==Qt::Key_H){

//        bullet_Timer_R.stop();

//        for(int i=0;i<BULLET_NUM;i++){
//            m_aqua.m_bullets[i].m_Free=true;
//        }
//        update();
//    }

}



void gamingScoll::on_exit_clicked()
{
    this->close();
    bgm->stop();
}

void gamingScoll::on_continue_button_clicked() //點下開始案件
{
    gameStart();
    ui->widget->close();

}
