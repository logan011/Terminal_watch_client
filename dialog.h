#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTime>
#include<QDate>
namespace Ui {
class Dialog;
}
struct Option
{
    bool power, carry_on,water;
    double volt12,volt5;
    QString t;
    Option(){power=carry_on=false; volt5=volt12=0.0; t = "";}
};

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
    void sendtomain(Option *op);
private:
    Ui::Dialog *ui;
    Option *option;
};

#endif // DIALOG_H
