#include "getvisualfromch.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()),this, SLOT(pBClicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()),this, SLOT(pB2Clicked()));
    connect(ui->pushButton_3, SIGNAL(clicked()),this, SLOT(pB3Clicked()));
    connect(ui->pushButton_4, SIGNAL(clicked()),this, SLOT(pB4Clicked()));
    connect(ui->pushButton_5, SIGNAL(clicked()),this, SLOT(pB5Clicked()));


    GetVisualFromCH Car(ui);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::pBClicked(){
    GetVisualFromCH Car(ui);
    Car.charts("speed","blue",ui->widget,0);
    Car.charts("refueling","red",ui->widget,1);
}
void Widget::pB2Clicked(){
    GetVisualFromCH Car(ui);
    Car.charts("acceleration","blue",ui->widget,0);
    Car.charts("refueling","red",ui->widget,1);
}
void Widget::pB3Clicked(){
    GetVisualFromCH Car(ui);
    Car.charts("lengthWay","blue",ui->widget,0);
    Car.charts("refueling","red",ui->widget,1);
}
void Widget::pB4Clicked(){
    GetVisualFromCH Car(ui);
    Car.charts("fuel","blue",ui->widget,0);
    Car.charts("refueling","red",ui->widget,1);
}
void Widget::pB5Clicked(){
    GetVisualFromCH Car(ui);
    Car.charts("acceleration","blue",ui->widget,0);
    Car.charts("refueling","red",ui->widget,1);
}
