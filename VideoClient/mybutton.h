#ifndef MYBUTTON_H
#define MYBUTTON_H
/* 自定义按钮类 */
#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButton(QWidget *parent = 0);
protected:
    void  mousePressEvent(QMouseEvent *e);
signals:

public slots:
};

#endif // MYBUTTON_H
