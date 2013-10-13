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
enum {Money_Dropped,Power,Carry_on,Disconnected,First_packet};
struct date{
    void setstruct(int message =-1,quint16 id=-1,bool pow=false,bool carry=false,double temp=20, double water=50000.0,quint16 money=0,QString t = "") {
        this->msg = message;
        this->Temprete = temp;
        this->Water_left = water;
        this->CountMoney = money;
        this->power = pow;
        this->carry_on = carry;
        this->ID = id;
        this->time = t;
    }
    double Temprete,Water_left;
    quint16 CountMoney;
    bool power, carry_on;
    quint16 ID;
    int msg;
    QString time;
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
    void slotpowerchange(int);
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
