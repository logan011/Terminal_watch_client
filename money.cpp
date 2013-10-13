#include "money.h"
#include<QDebug>
#include<QtGui>
#include <QApplication>
Money::Money(QWidget *parent):QGraphicsView(parent)
{
    QGraphicsScene  *scene= new QGraphicsScene();
    QPixmap rt;
    if(!rt.load(":/new/prefix1/money.jpg"))
        qDebug()<<"Eror open file";
   pixmap = new QPixmap(this->size());
    if(!pixmap->load(":/new/prefix1/vart.jpg"))
        qDebug()<<"Eror open file";
   scene->addPixmap(rt);
    setAcceptDrops(true);
    setMouseTracking(true);
    this->setScene(scene);
    this->setFrameShape(NoFrame);
    this->setFixedSize(100,100);
}
void Money::makeDrag()
{

    QDrag *dr = new QDrag(this);
    QMimeData *data = new QMimeData;
    data->setText("This is a test");
    dr->setMimeData(data);
    dr->setPixmap(*pixmap);
    dr->start();
}
void Money::mouseMoveEvent(QMouseEvent *pe)
{
    if(pe->buttons()  & Qt::LeftButton)
    {
        int distance = (pe->pos()- pos).manhattanLength();
        if(distance> QApplication::startDragDistance())
        {
            makeDrag();
        }
    }
}
void  Money::mousePressEvent(QMouseEvent * pe)
{
    if(pe->button() == Qt::LeftButton)
    {
        pos = pe->pos();
    }
    QWidget::mousePressEvent(pe);

}

