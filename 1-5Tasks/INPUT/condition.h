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
#include <mqtt/client.h>
#include <mqtt/callback.h>
#include <mqtt/connect_options.h>
#include <mqtt/topic.h>
#include <QProcess>
#include <MQTTClient.h>


using namespace clickhouse;
using namespace mqtt;

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
  Client * clientDB;
  Ui::MainWindow *ui;

public:
    int pause;
    Condition(Client *clientDB, Ui::MainWindow *ui, vector<int> *vecVals, vector<string> *vecNames, int drop);
     void changeParams();
     void simpleChangeParams();
     void state(int i);
     void insertBD(int id);
     void insertBDFromMQTT();
     void dropTable();
     void truncateTable();
     void widgetSimpleParams();
     void addSimple();




};

#endif // CONDITION_H
