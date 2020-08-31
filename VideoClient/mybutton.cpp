#include "mybutton.h"

MyButton::MyButton(QWidget *parent) : QPushButton(parent)
{
    this->setFlat(true);
}

void MyButton::mousePressEvent(QMouseEvent *e)
{
//    Q_UNUSED(e);
    if(e->button() == Qt::LeftButton)
    {
        emit clicked();
    }
}
