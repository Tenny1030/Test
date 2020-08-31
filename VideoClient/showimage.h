#ifndef SHOWIMAGE_H
#define SHOWIMAGE_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QLinearGradient> //渐变效果
#include <QStackedLayout> //栈布局
#include <QDateTime>

#include "mybutton.h" //自定义的按钮
#include "dialog.h"  //自定义对话框
#include "fullscreen.h" //自定义对话框(全屏)
#include "mythread.h" //自定义 线程类

class ShowImage : public QWidget
{
    Q_OBJECT
public:
    explicit ShowImage(QWidget *parent = 0);
    ~ShowImage();
    void brushColor();
protected:
    void  paintEvent(QPaintEvent *event);//绘制事件
signals:
    void  removeGUI(ShowImage *);
public slots:
    void  startBtnSlot();
    void  pauseBtnSlot();
    void  fullScreenBtnSlot();
    void  photoBtnSlot();
    void  videoBtnSlot();
    void  stopRecordBtnSlot();
    void  exitBtnSlot();
    void  receiveImage(QImage image);
    void  setBtnEnable();
private:
    QImage  image; //图片
    //按钮
    MyButton  *startBtn;
    MyButton  *pauseBtn;
    MyButton  *fullScreenBtn;
    MyButton  *photoBtn;
    MyButton  *videoBtn;
    MyButton  *stopRecordBtn;
    MyButton  *exitBtn;
    //
    QStackedLayout  *stacked;
    QStackedLayout  *stacked2;
    QString ip;
    int port;
    bool  net;
    //
    MyThread  *th;
};

#endif // SHOWIMAGE_H
