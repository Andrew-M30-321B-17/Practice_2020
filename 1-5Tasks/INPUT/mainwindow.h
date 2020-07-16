#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <vector>
#include <iostream>
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    vector<int> vecVals;
    vector<string> vecNames;
private slots:
    void hashSlot();
    void truncate();
    void drop();
    void sliderSlot();
    void update(int i);
    void addSimple();
    void checkBox(bool checked);
private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
