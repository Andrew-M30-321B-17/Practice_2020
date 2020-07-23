#include "getvisualfromch.h"
using namespace clickhouse;
GetVisualFromCH::GetVisualFromCH(Ui::Widget *poui)
{
    this->poui = poui;

    Client client(ClientOptions().SetHost("localhost"));

    string nsql = "SELECT MIN(timeOfWay) FROM Practice.condition";

    client.Select(nsql, [poui] (const Block& block)
        {
           for (size_t i = 0; i < block.GetRowCount(); i++){
               poui->lineEdit->setText(QString::number(block[0]->As<ColumnUInt64>()->At(i)));
               poui->horizontalSlider->setMinimum(block[0]->As<ColumnUInt64>()->At(i));
               poui->horizontalSlider_2->setMinimum(block[0]->As<ColumnUInt64>()->At(i));
            }
        });
    nsql = "SELECT MAX(timeOfWay) FROM Practice.condition";
    client.Select(nsql, [poui] (const Block& block)
        {
           for (size_t i = 0; i < block.GetRowCount(); i++){
               poui->lineEdit_2->setText(QString::number(block[0]->As<ColumnUInt64>()->At(i)));
               poui->horizontalSlider->setMaximum(block[0]->As<ColumnUInt64>()->At(i));
               poui->horizontalSlider_2->setMaximum(block[0]->As<ColumnUInt64>()->At(i));
               if(poui->horizontalSlider_2->value() == poui->lineEdit->text().toInt())poui->horizontalSlider_2->setValue(block[0]->As<ColumnUInt64>()->At(i));
           }

        });


    charts("tempIn","red",poui->widget_2,0);
    charts("tempOut","green",poui->widget_2,1);
    charts("conditioner","blue",poui->widget_2,1);
    charts("xPos","blue",poui->widget_3,0);

}

void GetVisualFromCH::charts(string name, string color, QCustomPlot * w, int num){

    QVector<double> X,Y;
    vector<string> vecSimpleNames;
    if(name == "Simple"){
        //draw(&X,&Y,"","black",w,0);
        Client client(ClientOptions().SetHost("localhost"));
        client.Select("DESCRIBE TABLE Practice.condition",[&vecSimpleNames](const Block& block){
            for (size_t i = 0; i < block.GetRowCount(); i++){

                string nameCut= block[0]->As<ColumnString>()->At(i);
                int len = nameCut.length();
                nameCut = nameCut.erase(min(6,len),len);

                if(nameCut == "Simple"){
                   vecSimpleNames.push_back(block[0]->As<ColumnString>()->At(i));

                }
            }

        });
        string colorM[10] ={"red","green","blue","yellow","pink","lime","orange","purple","gray","black"};
        for(size_t i =0;i <vecSimpleNames.size();i++ )
            if(i < 10)
                connectCH(&X,&Y,vecSimpleNames[i],colorM[i],w,i);
            else
                connectCH(&X,&Y,vecSimpleNames[i],colorM[9],w,i);

    }else
    connectCH(&X,&Y,name,color,w,num);
}

void GetVisualFromCH::connectCH(QVector<double> *X, QVector<double> *Y, string name, string color, QCustomPlot * w,int num){


    string sql;

    Client client(ClientOptions().SetHost("localhost"));
    int maxTime = max(poui->lineEdit_3->text().toInt(),poui->lineEdit_4->text().toInt());
    int minTime = min(poui->lineEdit_3->text().toInt(),poui->lineEdit_4->text().toInt());
    string dop = " WHERE timeOfWay >= "+QString::number(minTime).toStdString()+" AND timeOfWay <= "+QString::number(maxTime).toStdString();
    if(name == "xPos")sql = "SELECT yPos,xPos FROM Practice.condition"+dop;
        else  sql= "SELECT "+name+",timeOfWay FROM Practice.condition"+dop;
    client.Select(sql, [X,Y,name] (const Block& block)
        {
            string nameCut = name;
            int len = name.length();
            nameCut = nameCut.erase(min(6,len),len);


            for (size_t i = 0; i < block.GetRowCount(); ++i) {

                   if(name == "acceleration" or nameCut == "Simple"){ Y->push_back((double)block[0]->As<ColumnInt64>()->At(i));}
                   else Y->push_back((double)block[0]->As<ColumnUInt64>()->At(i));
                   X->push_back((double)(block[1]->As<ColumnUInt64>()->At(i)));

            }


        }
    );
    if(X->size() > 0 and Y->size()>0)
    draw(X,Y,name,color,w,num);

    //
}
void GetVisualFromCH::draw(QVector<double> *X, QVector<double> *Y, string name, string color, QCustomPlot *w, int num){


    QColor colorq = QColor(0,0,0);
    if (color == "red") colorq = QColor(255,0,0);
    if (color == "green") colorq = QColor(0,255,0);
    if (color == "blue") colorq = QColor(0,0,255);
    if (color == "yellow") colorq = QColor(255,255,0);
    if (color == "pink") colorq = QColor(255,0,255);
    if (color == "lime") colorq = QColor(0,255,255);
    if (color == "orange") colorq = QColor(255,165,0);
    if (color == "purple") colorq = QColor(160,32,240);
    if (color == "gray") colorq = QColor(139,139,139);
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
