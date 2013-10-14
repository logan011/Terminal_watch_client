#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this, SLOT(close()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(slotSaveData()));
    option = new Option();
}
void Dialog::slotShowDialog()
{
    this->show();
}
void Dialog::slotSaveData()
{
    option->power = ui->checkBox->isChecked();
    option->carry_on = ui->checkBox_2->isChecked();
    option->water = ui->checkBox_3->isChecked();
    if(ui->checkBox_3->isChecked())
        option->t = QTime::currentTime().toString() +"/" + QDate::currentDate().toString(Qt::SystemLocaleShortDate);
    option->volt5 = ui->doubleSpinBox->value();
    option->volt12 = ui->doubleSpinBox_2->value();
    emit sendtomain(option);
    ui->checkBox_3->setChecked(false);
}

Dialog::~Dialog()
{
    delete ui;
}
