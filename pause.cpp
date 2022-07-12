#include "pause.h"
#include "ui_pause.h"
#include"mainwindow.h"

Pause::Pause(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Pause)
{
    ui->setupUi(this);
}

Pause::~Pause()
{
    delete ui;
}

void Pause::on_buttonBox_accepted()
{
   MainWindow *newMain=new MainWindow;
   newMain->show();

}
