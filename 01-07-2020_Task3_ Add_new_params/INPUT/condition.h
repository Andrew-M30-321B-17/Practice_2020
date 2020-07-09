#ifndef CONDITION_H
#define CONDITION_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QtCore/QCoreApplication>
#include <clickhouse/client.h>
#include <ctime>
#include <string>
#include <cstdlib>
#include <math.h>
#include <thread>
#include <QMutex>
using namespace clickhouse;


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
         lengthWay,
         timeOfWay,
        colSimple;
  string sql;
  vector<int> * vecVals;
  vector<string> * vecNames;
  Client * client;
  Ui::MainWindow *ui;

public:
    int pause;
    Condition(Client *client, Ui::MainWindow *ui, vector<int> *vecVals, vector<string> *vecNames, int drop);
     void changeParams();
     void simpleChangeParams();
     void state(int i);
     void insertBD(int id);
     void dropTable();
     void truncateTable();
     void widgetSimpleParams();
     void addSimple();



};

#endif // CONDITION_H
