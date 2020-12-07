    #include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myrec.h"
#include "memmory.cpp"
#define hole Qt::white
#define segment QColor(110, 164, 250,255)

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    ui->graphicsView->setScene(scene);
    QLabel *name = new QLabel(this);
    QLabel *size = new QLabel(this);
    name->setText("Name");
    ui->gridLayout->addWidget(name,0,1);
    size->setText("Size");
    ui->gridLayout->addWidget(size,0,2);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_spinBox_4_valueChanged(int arg1)
{
    for (int i = n;i<arg1;i++) {
        QSpinBox *size = new QSpinBox(this);
        QLineEdit *name = new QLineEdit(this);
        QLabel *label = new QLabel(this);
        size->setMaximum(1000000000);
        label->setText("Segment " + QString::number(i));
        ui->gridLayout->addWidget(label,i+1,0);
        ui->gridLayout->addWidget(name,i+1,1);
        ui->gridLayout->addWidget(size,i+1,2);
        Label.append(label);
        Size.append(size);
        Name.append(name);
    }

    for (int i = arg1;i<n;i++) {
        ui->gridLayout->removeWidget(Size[i]);
        ui->gridLayout->removeWidget(Label[i]);
        ui->gridLayout->removeWidget(Name[i]);
        delete Size[i];
        delete Label[i];
        delete Name[i];
    }

    Size.erase(Size.begin()+arg1, Size.end());
    Label.erase(Label.begin()+arg1, Label.end());
    Name.erase(Name.begin()+arg1, Name.end());
    n = arg1;
}

void MainWindow::on_Process_clicked()
{
    bool flag = true;
    ui->pro->clear();
    map<QString,int> segments;
    for (int i =0;i < ui->spinBox_4->value();i++) {
        segments[Name[0]->text()] = Size[0]->value();
        if(ui->First->isChecked()){
            if(!firstFit(index,segments,holes,occupied,process)){
                ui->pro->setText("Failed to add Process please dealloacte to continue");
                flag = false;
            }
            else {
                ui->gridLayout->removeWidget(Size[0]);
                ui->gridLayout->removeWidget(Label[0]);
                ui->gridLayout->removeWidget(Name[0]);
                delete Size[0];
                delete Label[0];
                delete Name[0];
                Size.erase(Size.begin());
                Label.erase(Label.begin());
                Name.erase(Name.begin());
            }
        }
        else if(ui->Best->isChecked()){
            if(!bestFit(index,segments,holes,occupied,process)){
                ui->pro->setText("Failed to add Process please dealloacte to continue");
                flag = false;
            }
            else {
                ui->gridLayout->removeWidget(Size[0]);
                ui->gridLayout->removeWidget(Label[0]);
                ui->gridLayout->removeWidget(Name[0]);
                delete Size[0];
                delete Label[0];
                delete Name[0];
                Size.erase(Size.begin());
                Label.erase(Label.begin());
                Name.erase(Name.begin());
            }
        }

        else {
            ui->pro->setText("Please Select method of allocation");
            flag = false;
        }
        draw();
    }
    if(flag){
        index++;
        n=0;
        ui->spinBox_4->setValue(0);
        ui->pro->setText("Process added successfully");
    }
}

void MainWindow::on_Hole_clicked()
{
    holes[ui->start->value()] = ui->size->value();
    draw();
}

void MainWindow::de(int index)
{
    deallocation(index,holes,occupied,process);
    draw();
}

void MainWindow::tableDraw(int index)
{
    vector<indexSize> t = process[index];
    int row = t.size();
    delete  table;
    table = new QTableWidget(row,3);
    QTableWidgetItem *name = new QTableWidgetItem();
    name->setText("Name");
    QTableWidgetItem *base = new QTableWidgetItem();
    base->setText("Base");
    QTableWidgetItem *limit = new QTableWidgetItem();
    limit->setText("Limit");
    table->setHorizontalHeaderItem(0,name);
    table->setHorizontalHeaderItem(1,base);
    table->setHorizontalHeaderItem(2,limit);
    for (int j = 0;j < row;j++) {
        QTableWidgetItem *name = new QTableWidgetItem();
        name->setText(t[j].name);
        QTableWidgetItem *base = new QTableWidgetItem();
        base->setText(QString::number(t[j].index));
        QTableWidgetItem *limit = new QTableWidgetItem();
        limit->setText(QString::number(t[j].size));
        table->setItem(j,0,name);
        table->setItem(j,1,base);
        table->setItem(j,2,limit);
    }
    ui->gridLayout_2->addWidget(table);
}

void MainWindow::draw(){
    scene->clear();
    QPen pen;
    pen.setWidth(3);
    scene->addRect(70,0,300,ui->total->value(),pen,QBrush(segment));
    QGraphicsTextItem *texttime =scene->addText("0",QFont("sanserif"));
    texttime->setPos(0,-20);
    QGraphicsTextItem *end =scene->addText(QString::number(ui->total->value()),QFont("sanserif"));
    end->setPos(0,ui->total->value()-20);
    for (auto it = occupied.begin();it != occupied.end();it++) {
        int add = it->first;
        int size = it->second.size;
        int index = it->second.index;
        QGraphicsTextItem *texttime =scene->addText(QString::number(add),QFont("sanserif"));
        texttime->setPos(0,add-20);
        QGraphicsTextItem *end =scene->addText(QString::number(add+size),QFont("sanserif"));
        end->setPos(0,add+size-20);
        Myrec *rec = new Myrec(70,add,300,size,index);
        rec->setBrush(QBrush(segment));
        scene->addItem(rec);
        QGraphicsTextItem *name =scene->addText("P" + QString::number(index) + "\n" +it->second.name ,QFont("sanserif"));
        name->setPos(70,add);
        connect(rec,SIGNAL(dellacotian(int)),this,SLOT(de(int)));
        connect(rec,SIGNAL(table(int)),this,SLOT(tableDraw(int)));
    }
    for (auto it = holes.begin();it != holes.end();it++) {
        int add = it->first;
        int size = it->second;
        QGraphicsTextItem *texttime =scene->addText(QString::number(add),QFont("sanserif"));
        texttime->setPos(0,add-20);
        QGraphicsTextItem *end =scene->addText(QString::number(add+size),QFont("sanserif"));
        end->setPos(0,add+size-20);
        scene->addRect(70,add,300,size,pen,QBrush(hole));
    }


}
