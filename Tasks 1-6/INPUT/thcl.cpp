#include "thcl.h"
#include <QDebug>
int stop = 0;

thcl::thcl(Ui::MainWindow *ui, int val, string action,vector<int> * vecVals, vector<string> * vecNames,int drop, string api)
{
    this->ui = ui;
    this->action = action;
    this->drop = drop;
    this->vecVals = vecVals;
    this->vecNames = vecNames;
    this-> api = api;
    stop = val;
}

void thcl::run()
{


    Client clientDB(ClientOptions().SetHost("localhost"));
    Condition Car(&clientDB,ui,vecVals,vecNames,drop);

    if(api == "api"){
        string ans = Car.api(action+'/');
        if(ans == "stop_api") stop = 1;
            else if(ans == "start_api")this->save(&Car,"api");

    }
    else{


    if(action == "drop")Car.dropTable();
    else if(action == "trunc")Car.truncateTable();
    else if(action == "addSimple")Car.addSimple();
    else if(action == "mqtt")Car.insertBDFromMQTT();
    else this->save(&Car,"");

    }

}

void thcl::save(Condition * Car,string api){

    int i = 0;
     while(stop != 1) {

            QMutex mutex;
            mutex.lock();
            mutex.tryLock(1000);
            mutex.unlock();
            Car->changeParams();
            Car->simpleChangeParams();
            mutex.lock();
            mutex.tryLock(Car->pause*1000-1000);
            mutex.unlock();
            if(api != "api")Car->insertBD(i);
            else Car->insertAPI(i);
            i++;
            emit send(i);

        }

         Car->newsel();

}
