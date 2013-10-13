#ifndef BANK_H
#define BANK_H
#include <QLabel>
#include <QDrag>
#include<QDropEvent>
#include <QPropertyAnimation>
#include <QPushButton>
class Bank: public QLabel
{
    Q_OBJECT
public:
    Bank(QWidget *parent=0);
protected:
   void dragEnterEvent(QDragEnterEvent *);
    void  dropEvent(QDropEvent *);
signals:
    void signalMoneyDropped(int countmoney);
private:
      int countMoney;
};

#endif // BANK_H
