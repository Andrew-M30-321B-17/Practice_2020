#ifndef THCL_H
#define THCL_H
#include <QThread>
#include "condition.h"

class thcl : public QThread
{
Q_OBJECT
public:
    explicit thcl(Ui::MainWindow *ui, int val,string action);
    void run();

signals:
    void send(int i);

private:
    Ui::MainWindow *ui;
    string action;
};

#endif // THCL_H
