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
struct date{
    date(){Temprete = 20.0;Water_left = 50000;volt5 = 4;volt12 = 11; CountMoney =0; power = carry_on = false,ID = msg= -1;timesale= timewater = "";}
    void setstruct(int message,double Temp, double Water, double Vol5, double Vol12, int Mon, bool Power, bool Carry, int Id,QString TimeS, QString TimeW) {
        this->msg = message;
        this->Temprete = Temp;
        this->Water_left = Water;
        this->volt5 = Vol5;
        this->volt12 = Vol12;
        this->CountMoney = Mon;
        this->power = Power;
        this->carry_on = Carry;
        this->ID = Id;
        this->timesale = TimeS;
        this->timewater = TimeW;
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
    void slotsavedata(date *op);
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
