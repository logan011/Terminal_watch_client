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
    connect(ui->checkBox,SIGNAL(stateChanged(int)),this,SLOT(slotpowerchange(int)));
    connect(ui->checkBox_2,SIGNAL(stateChanged(int)),this,SLOT(slotpowerchange(int)));
    connect(ui->pushButton_3,SIGNAL(clicked()),subdialog,SLOT(slotShowDialog()));
    emit ui->pushButton->clicked(true);
}
void Widget::slotpowerchange(int state)
{
    QCheckBox *tmp = qobject_cast<QCheckBox *>(sender());
    if(tmp->objectName() == "checkBox")
    {
 dataToSend.setstruct(Power,Id,state,ui->checkBox_2->isChecked());
    }
    else if(tmp->objectName()== "checkBox_2")
    {
        dataToSend.setstruct(Carry_on,Id,ui->checkBox_2->isChecked(),state);
    }
 QByteArray data = serialize(dataToSend);
 socket->write(data);
}
void Widget::slotsendstruct()
{
    dataToSend.setstruct(Money_Dropped,Id,ui->checkBox->isChecked(),ui->checkBox_2->isChecked(),20,50000,0,time->currentTime().toString()+ Date->currentDate().toString());
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
   dataToSend.setstruct(Disconnected,Id);
    QByteArray data = serialize(dataToSend);
    socket->write(data);
}
void Widget::slotsendtoserver(int countmoney)
{
    dataToSend.setstruct(Money_Dropped,Id,ui->checkBox->isChecked(),ui->pushButton_2->isChecked(),20,dataToSend.Water_left -=250.0,countmoney);
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
    out<<packet.msg;
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

