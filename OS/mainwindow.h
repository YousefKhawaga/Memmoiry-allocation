#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

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

    void on_pushButton_2_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QList<QDoubleSpinBox*> Arrival;
    QList<QDoubleSpinBox*> Burst;
    QList<QDoubleSpinBox*> Priority;
    QList<QLabel*> Label;
    QList<QGraphicsRectItem*> Rec;
    QGraphicsScene *scene;
    QGridLayout *grid;
    QString type;
    QLabel * QueueLabel;
    QDoubleSpinBox* Queue;
    QLabel *priorityLabel;
    bool queueFlag=false,prflag=false;
protected:
};
#endif // MAINWINDOW_H
