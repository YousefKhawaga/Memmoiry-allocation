#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileSystemModel>
#include <QFileDialog>

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


void MainWindow::on_pushButton_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("select directory"),tr("C:/Users/youse/OneDrive/Desktop/"));
    if(directory == "")
        return ;
    QFileSystemModel *root = new QFileSystemModel();
    root->setRootPath(directory);
    ui->treeView->setModel(root);
    QModelIndex idx = root->index(directory);
    QModelIndex();
    ui->treeView->setRootIndex(idx);
    ui->treeView->show();

    if(root->directoryLoaded(directory))
        return;
}
