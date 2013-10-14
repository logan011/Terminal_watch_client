#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTime>
#include<QDate>
#include "widget.h"
namespace Ui {
class Dialog;
}
class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
public slots:
    void  slotShowDialog();
    void slotSaveData();
signals:
    void sendtomain(date *op);
private:
    Ui::Dialog *ui;
    date *optiondata;
};

#endif // DIALOG_H
