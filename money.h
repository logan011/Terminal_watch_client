#ifndef MONEY_H
#define MONEY_H
#include <QGraphicsView>
class Money: public QGraphicsView
{
    Q_OBJECT
public:
    void makeDrag();
    Money(QWidget *parent=0);
protected:
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void closeEvent(QCloseEvent *event) { emit signalclosewindow();}
signals:
    void signalclosewindow();
private:
    QPoint pos;
     QPixmap *pixmap;
};
#endif // MONEY_H
