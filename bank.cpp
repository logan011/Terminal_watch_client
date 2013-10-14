#include "bank.h"
#include <QMediaPlayer>
#include <QDebug>
#include <QLabel>
#include "widget.h"
Bank::Bank(QWidget *parent):QLabel(parent)
{
    setAcceptDrops(false);
    countMoney= 0;
    this->setPixmap(QString::fromUtf8(":/new/prefix1/bank.jpg"));
}
void Bank::dragEnterEvent(QDragEnterEvent *pe)
{
    if(!acceptDrops())
        qDebug()<<"take your water";
        pe->acceptProposedAction();
}
void Bank::dropEvent(QDropEvent *)
{
    QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("/home/roman/QtProject/TerminalWatchClient_/Moneta.mp3"));
    player->setVolume(100);
    player->play();
    setAcceptDrops(false);
    emit signalMoneyDropped(++countMoney);

}

