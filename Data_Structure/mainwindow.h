#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileSystemModel>
#include <QFileDialog>
#include <QListWidgetItem>
#include "Trie.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void Trie_input(QString directory);

    void on_pushButton_2_clicked();

    void on_listWidget_itemActivated(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    Trie* head = new Trie();
    QFileSystemModel *root = new QFileSystemModel();
};
#endif // MAINWINDOW_H
