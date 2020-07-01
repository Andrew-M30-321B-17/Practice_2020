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
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)),this, SLOT(sliderSlot()));
    connect(ui->horizontalSlider_2, SIGNAL(valueChanged(int)),this, SLOT(sliderSlot()));
    connect(ui->horizontalSlider_3, SIGNAL(valueChanged(int)),this, SLOT(sliderSlot()));
    connect(ui->horizontalSlider_4, SIGNAL(valueChanged(int)),this, SLOT(sliderSlot()));
    connect(ui->horizontalSlider_5, SIGNAL(valueChanged(int)),this, SLOT(sliderSlot()));

}
void MainWindow::update (int i)
{
ui->label_18->setText("Сохранено: "+QString::number(i));
}

void MainWindow::truncate(){

    thcl *thread= new thcl(ui,0,"trunc");
        connect(thread, SIGNAL(send(int)), this, SLOT(update(int)));
    thread->start();
}

void MainWindow::drop(){
    thcl *thread= new thcl(ui,0,"drop");
        connect(thread, SIGNAL(send(int)), this, SLOT(update(int)));
    thread->start();

}

void MainWindow::hashSlot(){

    if(ui->pushButton->isEnabled()){

        thcl *thread= new thcl(ui,0,"run");
            connect(thread, SIGNAL(send(int)), this, SLOT(update(int)));
        thread->start();
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);

    }else{

        thcl *thread= new thcl(ui,1,"stop");
            connect(thread, SIGNAL(send(int)), this, SLOT(update(int)));
        thread->start();
        ui->pushButton->setEnabled(true);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_4->setEnabled(true);

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
