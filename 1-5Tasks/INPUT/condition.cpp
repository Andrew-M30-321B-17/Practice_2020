#include "condition.h"

Condition::Condition(Client * clientDB, Ui::MainWindow * ui, vector<int> *vecVals, vector<string> *vecNames , int drop)
{
    this->clientDB = clientDB;
    this->ui = ui;
    this->vecVals = vecVals;
    this->vecNames = vecNames;
    if(drop ==1)dropTable();
    int i = 0;
    QString nameO = QString::fromStdString("SimpI")+ QString::number(i);
    QLineEdit * find = ui->widget->findChild<QLineEdit*>(nameO);
    while(find=ui->widget->findChild<QLineEdit*>(nameO)){
        i++;
        nameO = "SimpI"+ QString::number(i);
        //find = ui->widget->findChild<QLineEdit*>(nameO);
        int u =-1;
        for(size_t t = 0 ; t<vecNames->size();t++)
          if(vecNames->at(t) == find->placeholderText().toStdString()) u = i;

        if(u == -1){
            vecNames->push_back(find->placeholderText().toStdString());
             vecVals->push_back(find->text().toInt());
        }else
            vecVals->at(u) = find->text().toInt();
    }
    this->sql = "CREATE TABLE IF NOT EXISTS Practice.condition (id UInt64, timest DateTime, tempIn UInt64, tempOut UInt64, xPos UInt64, yPos UInt64, speed UInt64, acceleration Int64,fuel UInt64, conditioner UInt64, refueling UInt64, lengthWay UInt64, timeOfWay UInt64";
    for(size_t i = 0; i <vecNames->size();i++)if(vecNames->at(i) != "")sql+=", "+vecNames->at(i)+" Int64";
    cout << sql << endl;
    clientDB->Execute("CREATE DATABASE IF NOT EXISTS Practice");
    clientDB->Execute(sql+")ENGINE=Memory");
    tempIn = ui->lineEdit->text().toInt();
    tempOut = ui->lineEdit_2->text().toInt();
    xPos = ui->lineEdit_3->text().toInt();
    yPos = ui->lineEdit_4->text().toInt();
    speed = ui->lineEdit_5->text().toInt();
    acceleration = ui->lineEdit_6->text().toInt();
    fuel = ui->lineEdit_7->text().toInt();
    if(ui->radioButton->isChecked())conditioner = 1; else conditioner = 0;
    lengthWay = abs(ui->lineEdit_8->text().toInt());
    pause = ui->lineEdit_9->text().toInt();
    refueling = 0;
    timeOfWay = 0-pause;



}

void Condition::insertBDFromMQTT(){
        string topicName = ui->lineEdit_12->text().toStdString();
       system(("python3 /home/andrew/Practice_29-06-2020/createBD.py "+topicName+"2").c_str());

}

void Condition::widgetSimpleParams(){


    vector<string> vecSimpleNames;
           clientDB->Select("DESCRIBE TABLE Practice.condition",[&vecSimpleNames](const Block& block){
            for (size_t i = 0; i < block.GetRowCount(); i++){

                string nameCut= block[0]->As<ColumnString>()->At(i);
                int len = nameCut.length();
                nameCut = nameCut.erase(min(6,len),len);

                if(nameCut == "Simple"){
                   vecSimpleNames.push_back(block[0]->As<ColumnString>()->At(i));

                }
            }

        });

    cout <<  vecSimpleNames.size() << endl;
           for(size_t i =0;i <vecSimpleNames.size();i++ ){
                   QLabel * Label = new QLabel(ui->widget);
                   Label->setText(QString::fromStdString(vecSimpleNames[i]));
                   Label->setGeometry(0,i*40,100,25);
                   QLineEdit * Edit = new QLineEdit(ui->widget);
                   Edit->setGeometry(0,i*40+20,100,25);
                   Edit->setText("0");
                   Edit->setObjectName("SimpI"+QString::number(i));
                   Edit->setPlaceholderText(QString::fromStdString(vecSimpleNames[i]));

           }





}

void Condition::addSimple(){
    string name = ui->lineEdit_10->text().toStdString();


    // client->Execute("ALTER TABLE Practice.condition ADD COLUMN IF NOT EXISTS Simple"+name+" Int64 AFTER pause"); // движок Memory не поддерживает add column(


    int y = -1;
    for(size_t i = 0;i<vecNames->size();i++)
        if(vecNames->at(i) == "Simple"+name) y = i;

   if(y == -1){
    vecVals->push_back(ui->lineEdit_11->text().toInt());
    vecNames->push_back("Simple"+name);
    }else{
        vecVals->at(y) = ui->lineEdit_11->text().toInt();
    }

    dropTable();

    //client->Execute(sql+")ENGINE=Memory");
    ui->label_22->setText(ui->label_22->text()+QString::fromStdString("\n")+ui->lineEdit_10->text()+QString::fromStdString("=")+ui->lineEdit_11->text());


}

void Condition::simpleChangeParams(){

    for(size_t i=0;i<vecVals->size();i++)
        if(vecVals->at(i) > 100)vecVals->at(i) = 0;
        else vecVals->at(i)=vecVals->at(i)+2;


}

void Condition::changeParams(){

    if(tempOut >= 30)tempOut--;
    else if(tempOut <= -30)tempOut++;
    else  tempOut += pow(-1,rand());
    if(conditioner == 0) if(tempOut >=tempIn)tempIn++;else tempIn--;//если включен кондей, если снаружи холоднее чем внутри температура внутри падает, иначе растет
    else if(tempIn <26)tempIn++; else if(tempIn >28)tempIn--;
    if(tempIn>28 or tempIn<23)conditioner =1; else conditioner=0;//если температура внутри больше 28 или меньше 23 включаем кондей
    if(fuel>0) //если есть топливо
    {
        if(refueling == 0){ //и машина не на заправке
            if(speed >= 40)acceleration = 0; else if(acceleration<5)acceleration++;//
            speed+=acceleration; //увеличиваем скорость пока она не достигнет 40 метров в секунду
            int dLenght = (speed+acceleration*acceleration/2);//так как изменения происходя раз в секунду то путь за итерацию равен v+(a^2)/2
            lengthWay+=dLenght;
            xPos+=dLenght/5; //находим перемещение по х и у по теореме пифагора, задаем перемещение по у в 2 раза быстрее чем по х
            yPos+=2*dLenght/5; //тогда х^2+(2x)^2 = dLenght^2
            fuel--;
        }else{
            fuel+=20;
            if(fuel >= 200) refueling = 0;
        }
    }else{// если бензина нет дожидаемся остановки и начинаем заправку

        if(speed > 0){
            acceleration--;
            if(speed>=abs(acceleration))speed +=acceleration;else speed =0;

         }else{
             refueling = 1;
             fuel+=20;
             acceleration = 0;
             speed = 0;
        }
    }
    timeOfWay += pause;


}
void Condition::insertBD(int id){

    Block b;


    auto idCol = make_shared<ColumnUInt64>();
    idCol->Append(id);

    auto timeOfWayCol = make_shared<ColumnUInt64>();
    timeOfWayCol->Append(timeOfWay);

    auto timeCol = make_shared<ColumnDateTime>();
    timeCol->Append(time(NULL));

    auto tempInCol = make_shared<ColumnUInt64>();
    tempInCol->Append(tempIn);
    auto tempOutCol = make_shared<ColumnUInt64>();
    tempOutCol->Append(tempOut);

    auto xPosCol = make_shared<ColumnUInt64>();
    xPosCol->Append(xPos);
    auto yPosCol = make_shared<ColumnUInt64>();
    yPosCol->Append(yPos);

    auto speedCol = make_shared<ColumnUInt64>();
    speedCol->Append(speed);
    auto accelerationCol = make_shared<ColumnInt64>();
    accelerationCol->Append(acceleration);

    auto fuelCol = make_shared<ColumnUInt64>();
    fuelCol->Append(fuel);
    auto conditionerCol = make_shared<ColumnUInt64>();
    conditionerCol->Append(conditioner);

    auto refulingCol = make_shared<ColumnUInt64>();
    refulingCol->Append(refueling);
    auto lengthWayCol = make_shared<ColumnUInt64>();
    lengthWayCol->Append(lengthWay);



    b.AppendColumn("id",idCol);
    b.AppendColumn("timest", timeCol);
    b.AppendColumn("tempIn", tempInCol);
    b.AppendColumn("tempOut", tempOutCol);
    b.AppendColumn("xPos"  , xPosCol);
    b.AppendColumn("yPos", yPosCol);
    b.AppendColumn("speed", speedCol);
    b.AppendColumn("acceleration"  , accelerationCol);
    b.AppendColumn("fuel", fuelCol);
    b.AppendColumn("refueling", refulingCol);
    b.AppendColumn("lengthWay"  , lengthWayCol);
    b.AppendColumn("conditioner"  , conditionerCol);
    b.AppendColumn("timeOfWay" , timeOfWayCol);


    for(size_t i=0;i<vecVals->size();i++){ //for simple params
        if(vecNames->at(i) !=""){
        auto Col = make_shared<ColumnInt64>();
        Col->Append(vecVals->at(i));
        b.AppendColumn(vecNames->at(i),Col);
        }

    }

    clientDB->Insert("Practice.condition", b);
}

void Condition::dropTable(){

     clientDB->Execute("DROP TABLE IF EXISTS Practice.condition");

}
void Condition::truncateTable(){

     clientDB->Execute("TRUNCATE TABLE IF EXISTS Practice.condition");
}
