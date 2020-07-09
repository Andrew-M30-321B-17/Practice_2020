#ifndef THCL_H
#define THCL_H
#include <QThread>
#include "condition.h"

class thcl : public QThread
{
Q_OBJECT
public:
    explicit thcl(Ui::MainWindow *ui, int val, string action, vector<int> *vecVals, vector<string> *vecNames, int drop);
    void run();

signals:
    void send(int i);

private:
    Ui::MainWindow *ui;
    string action;
    vector<int> * vecVals;
    vector<string> * vecNames;
    int drop;

};

#endif // THCL_H
