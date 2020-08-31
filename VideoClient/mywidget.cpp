#include "mywidget.h"


Mywidget::Mywidget(QWidget *parent) : QDialog(parent)
{
    this->showMaximized();
}


void Mywidget::paintEvent(QPaintEvent *str)
{
    Q_UNUSED(str)
    QPainter  painter(this);
    painter.drawImage(QRect(0,0,this->width(),\
                            this->height()),imagex);
}

void Mywidget::receiveImage(QImage image)
{
    this->imagex = image;
    this->update();
}

