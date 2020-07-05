#include "getvisualfromch.h"
using namespace clickhouse;
GetVisualFromCH::GetVisualFromCH(Ui::Widget *poui)
{
    this->poui = poui;


    charts("tempIn","red",poui->widget_2,0);
    charts("tempOut","green",poui->widget_2,1);
    charts("conditioner","blue",poui->widget_2,1);
    charts("xPos","blue",poui->widget_3,0);

}

void GetVisualFromCH::charts(string name, string color, QCustomPlot * w, int num){

    QVector<double> X(2),Y(2);
    connectCH(&X,&Y,name,color,w,num);
}

void GetVisualFromCH::connectCH(QVector<double> *X, QVector<double> *Y, string name, string color, QCustomPlot * w,int num){


    string sql;
    Client client(ClientOptions().SetHost("localhost"));
    if(name == "xPos")sql = "SELECT yPos,xPos FROM Practice.condition";
        else  sql= "SELECT "+name+",timeOfWay FROM Practice.condition";
    client.Select(sql, [X,Y,name] (const Block& block)
        {

            for (size_t i = 0; i < block.GetRowCount(); ++i) {
                   X->resize(X->size()+1);
                   Y->resize(Y->size()+1);
                   if(name == "acceleration") Y->push_back((double)block[0]->As<ColumnInt64>()->At(i));
                   else Y->push_back((double)block[0]->As<ColumnUInt64>()->At(i));
                   X->push_back((double)(block[1]->As<ColumnUInt64>()->At(i)));

            }


        }
    );

    draw(X,Y,name,color,w,num);

    //
}
void GetVisualFromCH::draw(QVector<double> *X, QVector<double> *Y, string name, string color, QCustomPlot *w, int num){


    QColor colorq = QColor(0,0,0);
    if (color == "red") colorq = QColor(255,0,0);
    if (color == "green") colorq = QColor(0,255,0);
    if (color == "blue") colorq = QColor(0,0,255);
    QCPRange xRange = w->xAxis->range();
    QCPRange yRange = w->yAxis->range();


    double a = min(X->at(0),xRange.center()-xRange.size()/2);
    double b = max(X->at(X->size()-1),xRange.center()+xRange.size()/2);

    if(num != 0){
        num = w->graphCount();
    }else{
        w->yAxis->setLabel("");
        w->clearGraphs();
    }
    w->addGraph();
    w->graph(num)->setPen(colorq);
    w->graph(num)->setData(*X, *Y);
    string xLabel;
    if (name =="xPos"){xLabel = name;name = "yPos";}
    else xLabel = "time (m/s)";
    string yLabel = "|   "+name+"("+color+")   |";


    w->xAxis->setLabel(QString::fromStdString(xLabel));
    w->yAxis->setLabel(w->yAxis->label()+QString::fromStdString(yLabel));


    w->xAxis->setRange(a, b);

    double minY = Y->at(0), maxY = Y->at(0);
    for (int i=1; i<Y->size(); i++)
    {
        if (Y->at(i)<minY) minY = Y->at(i);
        if (Y->at(i)>maxY) maxY = Y->at(i);
    }
    maxY++;
    if(num != 0){
        minY = min(minY,yRange.center()-yRange.size()/2);
        maxY = max(maxY,yRange.center()+yRange.size()/2);
    }
    w->yAxis->setRange(minY, maxY);

    w->replot();
    X->clear();
    Y->clear();

}
