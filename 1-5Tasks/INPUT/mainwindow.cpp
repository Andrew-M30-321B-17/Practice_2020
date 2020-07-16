#include "thcl.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()),this, SLOT(hashSlot()));
    connect(ui->pushButton_2, SIGNAL(clicked()),this, SLOT(hashSlot()));
    connect(ui->pushButton_3, SIGNAL(clicked()),this, SLOT(truncate()));
    connect(ui->pushButton_4, SIGNAL(clicked()),this, SLOT(drop()));
    connect(ui->pushButton_5, SIGNAL(clicked()),this, SLOT(addSimple()));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)),this, SLOT(sliderSlot()));
    connect(ui->horizontalSlider_2, SIGNAL(valueChanged(int)),this, SLOT(sliderSlot()));
    connect(ui->horizontalSlider_3, SIGNAL(valueChanged(int)),this, SLOT(sliderSlot()));
    connect(ui->horizontalSlider_4, SIGNAL(valueChanged(int)),this, SLOT(sliderSlot()));
    connect(ui->horizontalSlider_5, SIGNAL(valueChanged(int)),this, SLOT(sliderSlot()));
    connect(ui->checkBox,SIGNAL(clicked(bool)),this,SLOT(checkBox(bool)));
    Client client(ClientOptions().SetHost("localhost"));
    Condition Car(&client,ui,&vecVals,&vecNames,0);
    Car.widgetSimpleParams();





}
void MainWindow::update (int i)
{
ui->label_18->setText("Сохранено: "+QString::number(i));
}

void MainWindow::truncate(){

    thcl *thread= new thcl(ui,0,"trunc",&vecVals,&vecNames,0);
        connect(thread, SIGNAL(send(int)), this, SLOT(update(int)));
    thread->start();
}

void MainWindow::drop(){
    thcl *thread= new thcl(ui,0,"drop",&vecVals,&vecNames,0);
        connect(thread, SIGNAL(send(int)), this, SLOT(update(int)));
    thread->start();

}

void MainWindow::addSimple(){

    thcl *thread= new thcl(ui,0,"addSimple",&vecVals,&vecNames,1);
        connect(thread, SIGNAL(send(int)), this, SLOT(update(int)));
    thread->start();
}

void MainWindow::hashSlot(){

    if(ui->checkBox->isChecked()){

        if(ui->lineEdit_12->text() == "") ui->label_22->setText(ui->label_22->text()+QString::fromStdString("\r\nВведите имя топика"));
            else{
                ui->label_22->clear();
                thcl *thread= new thcl(ui,1,"mqtt",&vecVals,&vecNames,1);
                    connect(thread, SIGNAL(send(int)), this, SLOT(update(int)));
                thread->start();

            }

    }else{



        if(ui->pushButton->isEnabled()){

            thcl *thread= new thcl(ui,0,"run",&vecVals,&vecNames,1);
                connect(thread, SIGNAL(send(int)), this, SLOT(update(int)));
            thread->start();
            ui->pushButton->setEnabled(false);
            ui->pushButton_2->setEnabled(true);
            ui->pushButton_3->setEnabled(false);
            ui->pushButton_4->setEnabled(false);

          }else{

            thcl *thread= new thcl(ui,1,"stop",&vecVals,&vecNames,0);
             connect(thread, SIGNAL(send(int)), this, SLOT(update(int)));
            thread->start();
            ui->pushButton->setEnabled(true);
            ui->pushButton_2->setEnabled(false);
            ui->pushButton_3->setEnabled(true);
            ui->pushButton_4->setEnabled(true);

            }

    }


}

void MainWindow::checkBox(bool checked){

    if(checked){
        ui->pushButton->setText("Write");
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
        ui->lineEdit_3->setEnabled(false);
        ui->lineEdit_4->setEnabled(false);
        ui->lineEdit_8->setEnabled(false);
        ui->lineEdit_9->setEnabled(false);
        ui->lineEdit_10->setEnabled(false);
        ui->lineEdit_11->setEnabled(false);
        ui->lineEdit_12->setEnabled(true);
        ui->label_22->clear();
        ui->widget->repaint();

    }else{
        ui->pushButton->setText("Start");
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_4->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
        ui->lineEdit_3->setEnabled(true);
        ui->lineEdit_4->setEnabled(true);
        ui->lineEdit_8->setEnabled(true);
        ui->lineEdit_9->setEnabled(true);
        ui->lineEdit_10->setEnabled(true);
        ui->lineEdit_11->setEnabled(true);
        ui->lineEdit_12->setEnabled(false);
    }

}

void MainWindow::sliderSlot(){

    ui->lineEdit->setText(QString::number(ui->horizontalSlider->value()));
     ui->lineEdit_2->setText(QString::number(ui->horizontalSlider_2->value()));
      ui->lineEdit_5->setText(QString::number(ui->horizontalSlider_3->value()));
       ui->lineEdit_6->setText(QString::number(ui->horizontalSlider_4->value()));
        ui->lineEdit_7->setText(QString::number(ui->horizontalSlider_5->value()));

}



MainWindow::~MainWindow()
{
    delete ui;
}
