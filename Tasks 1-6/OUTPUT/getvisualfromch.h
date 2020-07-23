#ifndef GETVISUALFROMCH_H
#define GETVISUALFROMCH_H
#include "widget.h"
#include "ui_widget.h"
#include <iostream>
#include <math.h>
#include <clickhouse/client.h>
using namespace  std;




class GetVisualFromCH
{

public:

    Ui::Widget * poui;
    GetVisualFromCH(Ui::Widget * poui);
    void connectCH(QVector<double> *X, QVector<double> *Y, string name, string color, QCustomPlot *w, int num);
    void draw(QVector<double> *X, QVector<double> *Y, string name, string color, QCustomPlot *w, int num);
    void charts(string name, string color, QCustomPlot * w, int num);
    void newsel();
};

#endif // GETVISUALFROMCH_H
