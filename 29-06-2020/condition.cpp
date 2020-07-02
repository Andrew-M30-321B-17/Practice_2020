#include "condition.h"

Condition::Condition(Client * client, Ui::MainWindow * ui)
{
    this->client = client;
    this->ui = ui;
    client->Execute("CREATE DATABASE IF NOT EXISTS Practice");
    client->Execute("CREATE TABLE IF NOT EXISTS Practice.condition (id UInt64, timest DateTime, tempIn UInt64, tempOut UInt64, xPos UInt64, yPos UInt64, speed UInt64, acceleration UInt64,fuel UInt64, conditioner UInt64, refueling UInt64, lengthWay UInt64, pause UInt64) ENGINE = Memory");
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
            if(acceleration<5)acceleration++;
            if(speed>=acceleration)speed -=acceleration;else speed =0;

         }else{
             refueling = 1;
             fuel+=20;
             acceleration = 0;
             speed = 0;
        }
    }


}
void Condition::insertBD(int id){

    Block b;

    auto idCol = make_shared<ColumnUInt64>();
    idCol->Append(id);

    auto pauseCol = make_shared<ColumnUInt64>();
    pauseCol->Append(pause);

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
    auto accelerationCol = make_shared<ColumnUInt64>();
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
    b.AppendColumn("pause" , pauseCol);


    client->Insert("Practice.condition", b);
}

void Condition::dropTable(){

     client->Execute("DROP TABLE IF EXISTS Practice.condition");
}
void Condition::truncateTable(){

     client->Execute("TRUNCATE TABLE IF EXISTS Practice.condition");
}
