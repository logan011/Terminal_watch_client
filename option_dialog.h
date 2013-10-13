#ifndef OPTION_DIALOG_H
#define OPTION_DIALOG_H

#include <QDialog>
namespace MU {
class Dialog;
}
class Dialog : public QWidget
{
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent = 0);

signals:

public slots:
    void slotCreateDialog();
private :
    MU::Dialog *mu;


};

#endif // OPTION_DIALOG_H
