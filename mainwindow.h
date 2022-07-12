#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMovie>
#include<QMediaPlayer>
#include"gaming.h"
#include"gamingscoll.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_radioButton_clicked();

    void on_gameModeFreedom_clicked();

    void on_gameModeScoll_clicked();

    void on_exit_clicked();

private:
    Ui::MainWindow *ui;
     QMediaPlayer *bgm=new QMediaPlayer(this);
     QMovie *firework = new QMovie(":/new/prefix1/icon/fireWorks.gif");
     QMovie *clouds =new QMovie(":/new/prefix1/icon/clouds.gif");
};

#endif // MAINWINDOW_H
