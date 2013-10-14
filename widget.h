#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QTcpSocket>
#include <QByteArray>
#include <QTime>
#include <QDate>
namespace Ui {
class Widget;
}
enum {Money_Dropped,Power,Carry_on,Disconnected,First_packet,Options};
struct Option;
struct date{
    date(){Temprete = 20.0;Water_left = 50000;volt5 = 4;volt12 = 11; CountMoney =0; power = carry_on = false,ID = msg= -1;timesale= timewater = "";}
    void setstruct(int message =-1,quint16 id=-1,double temp=20, double water=50000.0,quint16 money=0,QString t = "" ) {
        this->msg = message;
        this->Temprete = temp;
        this->Water_left = water;
        this->CountMoney = money;
        this->ID = id;
        this->timesale = t;
        //

    }
    void setstructoption(int message = -1, quint16 id = -1, bool pow = false, bool carry = false,bool water = false,double vol12 = 0.0, double vol5 = 0.0,QString t= "")
    {
        this->msg = message;
        this->ID = id;
        this->power = pow;
        this->carry_on = carry;
        if(water)
        {
        this->timewater = t;
          this->Water_left = 50000;
        }
        this->volt5 = vol5;
        this->volt12 = vol12;

    }

    double Temprete,Water_left,volt12,volt5;
    quint16 CountMoney;
    bool power, carry_on;
    quint16 ID;
    int msg;
    QString timesale, timewater;
};
class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
private:
    QByteArray serialize(date packet);
public slots:
    void showWater();
    void hideWater();
    void slotreadfromserver();
    void slotsendtoserver();
    void slotsendtoserver(int);
    void slotsendstruct();
    void slotsavedata(Option *op);
protected:
    void closeEvent(QCloseEvent *event);
signals:
    void signalclosewindow();
    void signalsenttoserver();
private:
    Ui::Widget *ui;
     QTcpSocket *socket;
     int Id;
     date  dataToSend;
     QTime *time;
     QDate *Date;
};


#endif // WIDGET_H
