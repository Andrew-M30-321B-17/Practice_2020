#include "thcl.h"
#include <QDebug>
int stop = 0;

thcl::thcl(Ui::MainWindow *ui, int val, string action,vector<int> * vecVals, vector<string> * vecNames,int drop)
{
    this->ui = ui;
    this->action = action;
    this->drop = drop;
    this->vecVals = vecVals;
    this->vecNames = vecNames;
    stop = val;
}

void thcl::run()
{
    Client clientDB(ClientOptions().SetHost("localhost"));

    Condition Car(&clientDB,ui,vecVals,vecNames,drop);

    if(action == "drop")Car.dropTable();
    else if(action == "trunc")Car.truncateTable();
    else if(action == "addSimple")Car.addSimple();
    else if(action == "mqtt")Car.insertBDFromMQTT();
    else{
        int i = 0;
         while(stop != 1) {

            QMutex mutex;
            mutex.lock();
            mutex.tryLock(1000);
            mutex.unlock();
            Car.changeParams();
            Car.simpleChangeParams();
            mutex.lock();
            mutex.tryLock(Car.pause*1000-1000);
            mutex.unlock();
            Car.insertBD(i);
            i++;
            emit send(i);

        }
    }
}
