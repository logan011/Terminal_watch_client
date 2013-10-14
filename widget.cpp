#include "widget.h"
#include "ui_widget.h"
#include<QPixmap>
#include "dialog.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
   socket = new QTcpSocket();
   socket->connectToHost("localhost",2323);
   Id = 0;
   time= new QTime();
   Date = new QDate();

  QPixmap pixmap(":/new/prefix1/water.jpg");
    QIcon ButtonIcon(pixmap);
    Dialog *subdialog = new Dialog();
   ui->pushButton->setIcon(ButtonIcon);
   ui->pushButton->setIconSize(pixmap.rect().size());
    ui->textBrowser->setReadOnly(true);
    ui->textBrowser->setTextColor(Qt::black);
    ui->textBrowser->setHtml("<H3><center>Ready for work..</center></H3>");
    //client connection
    connect(socket,SIGNAL(readyRead()),this,SLOT(slotreadfromserver()));
    connect(this,SIGNAL(signalclosewindow()),this,SLOT(slotsendtoserver()));
    connect(ui->label,SIGNAL(signalMoneyDropped(int)),this,SLOT(slotsendtoserver(int)));
    connect(this,SIGNAL(signalsenttoserver()),this,SLOT(slotsendstruct()));
    //other connection
    connect(ui->label,SIGNAL(signalMoneyDropped(int)),this,SLOT(showWater()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(hideWater()));
    connect(ui->pushButton_3,SIGNAL(clicked()),subdialog,SLOT(slotShowDialog()));
    connect(subdialog,SIGNAL(sendtomain(date*)),this,SLOT(slotsavedata(date*)));
    emit ui->pushButton->clicked(true);
}
void Widget::slotsavedata(date *op)
{
    if(op->timewater != "")
        dataToSend.Water_left = op->Water_left;
    dataToSend.setstruct(Options,dataToSend.Temprete,dataToSend.Water_left,op->volt5,op->volt12,dataToSend.CountMoney,op->power,
                         op->carry_on,dataToSend.ID,dataToSend.timesale,op->timewater);
    QByteArray data = serialize(dataToSend);
    socket->write(data);
}
void Widget::slotsendstruct()
{
    dataToSend.setstruct(Money_Dropped,20,50000,4,11,0,false,false,Id,"","");
    QByteArray data = serialize(dataToSend);
    socket->write(data);
}

void Widget::slotreadfromserver()
{
     Id = socket->readAll().toInt();
    this->setWindowTitle("Client "+QString::number(Id));
    emit signalsenttoserver();
}
void Widget::showWater()
{
  QPropertyAnimation *animation = new QPropertyAnimation(ui->pushButton,"geometry");
  animation->setDuration(1000);
   animation->setEasingCurve(QEasingCurve::Linear);
    animation->setEndValue(QRectF(170,20,179,271));
   animation->start();
   ui->textBrowser->setHtml("<H3><center><font color = #8A0808>Take your water !</color></center></H3>");
}
void Widget::slotsendtoserver()
{
   dataToSend.setstruct(Disconnected,dataToSend.Temprete,dataToSend.Water_left,dataToSend.volt5,dataToSend.volt12,dataToSend.CountMoney,dataToSend.power,
                        dataToSend.carry_on,dataToSend.ID,dataToSend.timesale,dataToSend.timewater);
    QByteArray data = serialize(dataToSend);
    socket->write(data);
}
void Widget::slotsendtoserver(int countmoney)
{
    dataToSend.setstruct(Money_Dropped,20,dataToSend.Water_left-=250.0,dataToSend.volt5,dataToSend.volt12,countmoney,dataToSend.power,
                         dataToSend.carry_on,Id,time->currentTime().toString()+":"+ Date->currentDate().toString(Qt::SystemLocaleShortDate),"");
   // dataToSend.setstruct(Money_Dropped,Id,20,dataToSend.Water_left -=250.0,countmoney,time->currentTime().toString()+":"+ Date->currentDate().toString(Qt::SystemLocaleShortDate));
    QByteArray data = serialize(dataToSend);
    socket->write(data);

}
QByteArray Widget::serialize(date packet)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out <<(quint32)packet.ID;
    out << (qint32)packet.CountMoney;
    out<< packet.power;
    out<<packet.carry_on;
    out<<packet.Temprete;
    out<<packet.Water_left;
    out<<packet.volt5;
    out<<packet.volt12;
    out<<packet.msg;
    out<<packet.timewater;
    out<<packet.timesale;
    return data;
}

void Widget::hideWater()
{
    ui->label->setAcceptDrops(true);
    ui->pushButton->setGeometry(170,1,179,1);
    ui->textBrowser->setHtml("<H3><center>Ready for work..</center></H3>");
}
void Widget::closeEvent(QCloseEvent *event)
{
    emit signalclosewindow();
}
Widget::~Widget()
{
    delete ui;
}

