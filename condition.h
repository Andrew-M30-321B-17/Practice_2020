#ifndef CONDITION_H
#define CONDITION_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QtCore/QCoreApplication>
#include <clickhouse/client.h>
#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>
#include <math.h>
#include <thread>
#include <QMutex>
using namespace clickhouse;
using namespace std;

class Condition
{
private:
  int tempIn,
         tempOut,
         xPos,
         yPos,
         speed,
         acceleration,
         fuel,
         conditioner,
         refueling,
         lengthWay;

  Client * client;
  Ui::MainWindow *ui;

public:
    int pause;
    Condition(Client *client, Ui::MainWindow *ui);
     void changeParams();
     void state(int i);
     void insertBD();
     void dropTable();
     void truncateTable();


};

#endif // CONDITION_H
