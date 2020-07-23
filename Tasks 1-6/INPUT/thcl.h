#ifndef THCL_H
#define THCL_H
#include <QThread>
#include "condition.h"

class thcl : public QThread
{
Q_OBJECT
public:
    explicit thcl(Ui::MainWindow *ui, int val, string action, vector<int> *vecVals, vector<string> *vecNames, int drop, string api);
    void run();
    void save(Condition * Car, string api);

signals:
    void send(int i);

private:
    Ui::MainWindow *ui;
    string action;
    vector<int> * vecVals;
    vector<string> * vecNames;
    int drop;
    string api;

};

#endif // THCL_H
