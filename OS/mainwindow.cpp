#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_spinBox_4_valueChanged(int arg1)
{
    for (int i = 0;i<arg1;i++) {

    }
    ui->Process->setGeometry(170,340+(22*arg1),93,27);
    ui->Process->show();
}

