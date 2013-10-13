#include "option_dialog.h"
#include <QVBoxLayout>
#include <QCheckBox>
Dialog::Dialog(QWidget *parent) :
    QWidget(parent),
    mu(new MU::Dialog)
{


    QVBoxLayout *layout = new QVBoxLayout();
          dialog= new QDialog;
          dialog->setWindowTitle("Option");
         //  dialog->setGeometry(23,34,50,50);
           layout->addWidget(new QCheckBox ("Power"));
           layout->addWidget(new QCheckBox("Carry_on"));
           layout->addWidget(new QCheckBox("Top up water"));
           this->setLayout(layout);

}
void Dialog::slotCreateDialog()
{
    dialog->show();
}
