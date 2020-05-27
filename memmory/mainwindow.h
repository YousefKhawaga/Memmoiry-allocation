#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTableWidget>
#include <struct.h>

using namespace std;



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
    void on_spinBox_4_valueChanged(int arg1);

    void on_Process_clicked();

    void on_Hole_clicked();

    void de(int index);

    void tableDraw(int index);

private:
    Ui::MainWindow *ui;
    QList<QSpinBox*> Size;
    QList<QLineEdit*> Name;
    QList<QLabel*> Label;
    QTableWidget *table;
    QGraphicsScene *scene;
    map<int,vector<indexSize>> process;
    map<int, int> holes;
    map<int, indexSize> occupied;
    int n=0,index=0;
    void draw();
};
#endif // MAINWINDOW_H
