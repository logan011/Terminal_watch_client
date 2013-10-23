#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this, SLOT(close()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(slotSaveData()));
    connect(ui->btn_Cancel,SIGNAL(clicked()),this,SLOT(close()));
    optiondata = new date();
}
void Dialog::slotShowDialog()
{
    this->show();
}
void Dialog::slotSaveData()
{
    optiondata->power = ui->checkBox->isChecked();
    optiondata->carry_on = ui->checkBox_2->isChecked();
    if(ui->checkBox_3->isChecked())
    {
        optiondata->timewater = QTime::currentTime().toString() +"  " + QDate::currentDate().toString(Qt::SystemLocaleShortDate);
        optiondata->Water_left = 50000;
    }
    if(ui->checkBox_4->isChecked())
    {
        optiondata->CountMoney = 0;
    }
    optiondata->volt5 = ui->doubleSpinBox->value();
    optiondata->volt12= ui->doubleSpinBox_2->value();
    optiondata->Temprete =ui->doubleSpinBox_3->value();
    emit sendtomain(optiondata);
    ui->checkBox_3->setChecked(false);
    ui->checkBox_4->setChecked(false);
}

Dialog::~Dialog()
{
    delete ui;
}
