#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
private slots:
    void pBClicked();
    void pB2Clicked();
    void pB3Clicked();
    void pB4Clicked();
    void pB5Clicked();
    void sl1Change();
    void sl2Change();

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
