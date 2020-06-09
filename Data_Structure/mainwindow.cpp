#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileSystemModel>
#include <QFileDialog>
#include <QThread>


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
    root->setRootPath(directory);

    qApp->setOverrideCursor(Qt::WaitCursor);
    connect(root,SIGNAL(directoryLoaded(QString)),this,SLOT(Trie_input(QString)));


}

void MainWindow::Trie_input(QString directory)
{

    qApp->restoreOverrideCursor();
    ui->treeView->setModel(root);
    QModelIndex parentIndex = root->index(directory);
    ui->treeView->setRootIndex(parentIndex);
    ui->treeView->show();
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    qApp->processEvents();
    int numRows = root->rowCount(parentIndex);
    ui->progress->setText("Creating Trie");
    ui->progressBar->setMaximum(numRows);
    for (int row = 0; row < numRows; ++row) {
        ui->progressBar->setValue(row+1);
        qApp->processEvents();
        QModelIndex childIndex = root->index(row, 0, parentIndex);
        QString path = root->filePath(childIndex);
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QString content = file.readAll();
        QStringList list = content.split(" ");
        for (int i = 0; i < list.size(); ++i){
            head->insert(list.at(i), path);
        }
    }
    ui->progress->setText("Trie Created");
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
}

void MainWindow::on_pushButton_2_clicked()
{
    QStringList files;
    files = head->search(ui->search->text());
    files.removeDuplicates();
    ui->listWidget->clear();
    ui->listWidget->addItems(files);
    int count = ui->listWidget->count();
    ui->count->setText("Found in "+QString::number(count)+" files");
    ui->textBrowser->setText("");

    //    for (auto i = files.begin(); i != files.end(); i++) {


    //        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    //            return;
    //        QString content = file.readAll();
    //        QWidget page;
    //        ui->tabWidget->addTab(page,);
    //        count++;

    //        qApp->processEvents();
    //    }
}


void MainWindow::on_listWidget_itemActivated(QListWidgetItem *item)
{
    QFile file(item->text());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }
    QString content = file.readAll();
    ui->textBrowser->setText(content);
    QString search = ui->search->text();
    QTextCharFormat fmt;
    fmt.setBackground(Qt::yellow);
    int index = content.indexOf(search,0);
    while(index != -1){
        QTextCursor cursor(ui->textBrowser->document());
        cursor.setPosition(index, QTextCursor::MoveAnchor);
        cursor.setPosition(index+search.length(), QTextCursor::KeepAnchor);
        cursor.setCharFormat(fmt);
        index = content.indexOf(search,index+search.length());
    }
    file.close();
}
