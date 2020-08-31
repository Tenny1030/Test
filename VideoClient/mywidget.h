#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QPaintEvent>
#include <QPainter>
#include <QMainWindow>
#include "mythread.h"
#include "mainwindow.h"

class Mywidget : public QDialog
{
    Q_OBJECT
public:
    explicit Mywidget(QWidget *parent = 0);
signals:
    void sendImage(QImage);
protected:
     void  paintEvent(QPaintEvent *str);
public slots:
     void  receiveImage(QImage image);
private:
    QImage  imagex; //图片

};

#endif // MYWIDGET_H
