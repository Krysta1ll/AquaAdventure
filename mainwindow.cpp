#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(800,600);
    this->setWindowTitle("阿夸大冒险");          //游戏主窗口的标题
    this->setWindowIcon(QIcon(":/new/prefix1/AppIcon.icns"));

    //遊戲菜單介面動圖_騎貓阿夸
    QMovie * aquaLoading=new QMovie(":/new/prefix1/icon/aqua.gif");
    ui->aquaLoading->setMovie(aquaLoading);
    aquaLoading->start();
    //bgm
    QString bgmUrl="/Users/wangtianyu/AquaAdventure2/audio/backGround.mp3";
    bgm->setMedia(QUrl::fromLocalFile(bgmUrl));
    bgm->setVolume(50);
    bgm->play();
    //介面動圖煙花
    ui->fireWork->setMovie(firework);
    firework->start();

    ui->clouds->setMovie(clouds);
    clouds->start();


}




MainWindow::~MainWindow()
{
    delete ui;
}





//關閉遊戲聲音
void MainWindow::on_radioButton_clicked()
{

    bgm->stop();
}


//點擊開始遊戲時執行的操作_自由模式
void MainWindow::on_gameModeFreedom_clicked()
{
    gaming *gamingWindow=new gaming;
    gamingWindow->show();

    bgm->stop();
}


//點擊開始遊戲時執行的操作_卷軸模式
void MainWindow::on_gameModeScoll_clicked()
{
    gamingScoll *scollWindow=new gamingScoll;
    scollWindow->show();

    bgm->stop();

}


//關閉遊戲窗口
void MainWindow::on_exit_clicked()
{
    this->close();
}
