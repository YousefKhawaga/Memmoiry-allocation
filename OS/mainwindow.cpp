#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "output.cpp"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox->addItem("FCFS");
    ui->comboBox->addItem("Non Preemptive SJF");
    ui->comboBox->addItem("Preemptive SJF");
    ui->comboBox->addItem("RR");
    ui->comboBox->addItem("Non Preemptive Priority");
    ui->comboBox->addItem("Preemptive Priority");
    grid = new QGridLayout(this);
    QLabel *label1 = new QLabel(this);
    label1->setText("Arrival");
    QLabel *label2 = new QLabel(this);
    label2->setText("Burst");
    grid->addWidget(label1,0,1);
    grid->addWidget(label2,0,2);
    ui->scrollAreaWidgetContents->setLayout(grid);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->graphicsView->setScene(scene);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    type = ui->comboBox->currentText();
    if(prflag){
        for (int i=((grid->count()-3)/4)-1;i>=0;i--) {
            grid->removeWidget(Arrival[i]);
            grid->removeWidget(Burst[i]);
            grid->removeWidget(Label[i]);
            grid->removeWidget(Priority[i]);
            delete Arrival[i];
            delete Burst[i];
            delete Label[i];
            delete Priority[i];
        }
         grid->removeWidget(priorityLabel);
         delete priorityLabel;
         prflag = false;
    }
    else {
        for (int i=((grid->count()-2)/3)-1;i>=0;i--) {
            grid->removeWidget(Arrival[i]);
            grid->removeWidget(Burst[i]);
            grid->removeWidget(Label[i]);
            delete Arrival[i];
            delete Burst[i];
            delete Label[i];
        }
    }
    Arrival.clear();
    Burst.clear();
    Label.clear();
    Priority.clear();
    for (int i=1;i<=ui->spinBox->value();i++) {
        QDoubleSpinBox *arrival = new QDoubleSpinBox(this);
        QDoubleSpinBox *burst = new QDoubleSpinBox(this);
        if(type == "Non Preemptive Priority" || type == "Preemptive Priority"){
            QDoubleSpinBox *priority = new QDoubleSpinBox(this);
            Priority.append(priority);
            grid->addWidget(priority,i,3);
        }
        arrival->setMaximum(100000);
        burst->setMaximum(100000);
        Arrival.append(arrival);
        Burst.append(burst);
        QLabel *label = new QLabel(this);
        label->setText("Process " + QString::number(i));
        Label.append(label);
        grid->addWidget(label,i,0);
        grid->addWidget(arrival,i,1);
        grid->addWidget(burst,i,2);
    }
    if((type == "Non Preemptive Priority"||type=="Preemptive Priority") && !prflag){
        priorityLabel = new QLabel(this);
        priorityLabel->setText("Priority");
        grid->addWidget(priorityLabel,0,3);
        prflag = true;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    double q;
    scene->clear();
    if(type == "RR"||type=="Preemptive Priority"){
        q = Queue->value();
        if (q ==0){
            ui->label_4->setText("Error Quantum can't equal 0");
            return ;
        }
    }
    else
        q = 0;
    int numberOfProcesses = ui->spinBox->value();
    list<properties> temp;
    double avwt;
    temp= Calc(numberOfProcesses, type, q, Arrival, Burst, Priority,avwt);
    ui->label_4->setText("Average Waiting Time= " + QString::number(avwt));

    QPen pen;
    pen.setWidth(3);
    double burst,index,start;
    for (auto i = temp.begin();i!=temp.end();) {
        index=i->index;
        start=i->startTime;
        burst = 0;
        while (index == i->index && type != "RR") {
            burst+=i->burstTime;
            i++;
            if (i == temp.end())
                break;
        }
        if (type == "RR"){
            burst+=i->burstTime;
            i++;
        }
        QGraphicsTextItem *texttime =scene->addText(QString::number(start),QFont("sanserif"));
        texttime->setPos(start*30-5,100);
        if (index == -1){

            QGraphicsTextItem *text =scene->addText("Idle",QFont("sanserif",-1,3));
            text->setPos(start*30,0);
            continue;
        }
        if (burst == 0){}
        else{
        QRect rec(start*30,0,burst*30,100);
        scene->addRect(rec,pen,QBrush(QColor(110, 164, 250,255)));
        QGraphicsTextItem *text =scene->addText("P"+QString::number(index),QFont("sanserif",-1,3));
        text->setPos(start*30,0);
        }

    }
    QGraphicsTextItem *texttime =scene->addText(QString::number(start+burst),QFont("sanserif"));
    texttime->setPos((start+burst)*30-5,100);
}


void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if((arg1 == "RR" || arg1 == "Preemptive Priority") && !queueFlag) {
        QueueLabel = new QLabel(this);
        QueueLabel->setText("Quantum");
        Queue = new QDoubleSpinBox(this);
        ui->formLayout->addRow(QueueLabel,Queue);
        queueFlag = true;
    }
    else if (arg1 != "RR" && arg1 != "Preemptive Priority" && queueFlag) {
        ui->formLayout->removeWidget(QueueLabel);
        delete QueueLabel;
        delete Queue;
        Queue = nullptr;
        queueFlag = false;

    }
}
