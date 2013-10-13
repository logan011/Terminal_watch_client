#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this, SLOT(close()));
}
void Dialog::slotShowDialog()
{
    this->show();
}

Dialog::~Dialog()
{
    delete ui;
}
