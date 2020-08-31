#include "fullscreen.h"

FullScreen::FullScreen(QWidget *parent) : QDialog(parent)
{
    this->showFullScreen();//全屏显示
    this->showMaximized();
}

void FullScreen::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter  painter(this);
    painter.drawImage(QRect(0,0,this->width(),\
                     this->height()),image);
    //绘制文字
    painter.setPen(QColor("blue"));
    painter.setFont(QFont("Console",35));
    painter.drawText(10,40,"Press key ESC quit");
}
//用来接收 线程类 发来的 图片信号
void FullScreen::receiveImage(QImage image)
{
    this->image = image;
    this->update();
}



