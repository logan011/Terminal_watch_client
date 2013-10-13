#-------------------------------------------------
#
# Project created by QtCreator 2013-10-01T23:19:35
#
#-------------------------------------------------

QT       += core gui
QT += multimedia
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled1
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    money.cpp \
    bank.cpp \
    dialog.cpp

HEADERS  += widget.h \
    dialog.h
HEADERS  +=    money.h
HEADERS  +=    bank.h

FORMS    += widget.ui \
    dialog.ui

RESOURCES += \
    res.qrc

