#include "thcl.h"
#include <QDebug>
int stop = 0;

thcl::thcl(Ui::MainWindow *ui, int val, string action)
{
    this->ui = ui;
    this->action = action;
    stop = val;
}

void thcl::run()
{
    Client client(ClientOptions().SetHost("localhost"));
    Condition Car(&client,ui);

    if(action == "drop")Car.dropTable();
    else if(action == "trunc")Car.truncateTable();
    else{
        int i = 0;
         while(stop != 1) {

            QMutex mutex;
            mutex.lock();
            mutex.tryLock(1000);
            mutex.unlock();
            Car.changeParams();
            mutex.lock();
            mutex.tryLock(Car.pause*1000-1000);
            mutex.unlock();
            emit send(i);
            i++;

        }
    }
}
