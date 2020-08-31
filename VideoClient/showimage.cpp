#include "showimage.h"
#include <QDebug>

ShowImage::ShowImage(QWidget *parent) : QWidget(parent)
{
    net = false;
    th = NULL;
    //构造按钮
    startBtn = new MyButton(this);
    startBtn->setGeometry(180,300,45,45);
    startBtn->setIcon(QIcon(":/images/Start.png"));
    startBtn->setIconSize(QSize(45,45));
    startBtn->setToolTip("Connect to Server");

    pauseBtn = new MyButton(this);
    pauseBtn->setGeometry(180,300,45,45);
    pauseBtn->setIcon(QIcon(":/images/Pause.png"));
    pauseBtn->setIconSize(QSize(45,45));
    pauseBtn->setToolTip("Pause Video");

    fullScreenBtn = new MyButton(this);
    fullScreenBtn->setGeometry(240,300,45,45);
    fullScreenBtn->setIcon(QIcon(":/images/FullScreen.png"));
    fullScreenBtn->setIconSize(QSize(45,45));
    fullScreenBtn->setToolTip("FullScreen Video");

    photoBtn = new MyButton(this);
    photoBtn->setGeometry(300,300,45,45);
    photoBtn->setIcon(QIcon(":/images/Photo.png"));
    photoBtn->setIconSize(QSize(45,45));
    photoBtn->setToolTip("Get a Photo");

    videoBtn = new MyButton(this);
    videoBtn->setGeometry(360,300,45,45);
    videoBtn->setIcon(QIcon(":/images/Video.png"));
    videoBtn->setIconSize(QSize(45,45));
    videoBtn->setToolTip("Start Record Video");

    stopRecordBtn = new MyButton(this);
    stopRecordBtn->setGeometry(360,300,45,45);
    stopRecordBtn->setIcon(QIcon(":/images/StopRecord.png"));
    stopRecordBtn->setIconSize(QSize(45,45));
    stopRecordBtn->setToolTip("Stop Record Video");

    exitBtn = new MyButton(this);
    exitBtn->setGeometry(420,300,45,45);
    exitBtn->setIcon(QIcon(":/images/Exit.png"));
    exitBtn->setIconSize(QSize(45,45));
    exitBtn->setToolTip("Close the Video");
    //栈布局
    stacked = new QStackedLayout;
    stacked->addWidget(startBtn);
    stacked->addWidget(pauseBtn);
    stacked2 = new QStackedLayout;
    stacked2->addWidget(videoBtn);
    stacked2->addWidget(stopRecordBtn);
    //
    brushColor();
    //绑定按钮的信号和槽
    connect(startBtn,SIGNAL(clicked(bool)),\
            this,SLOT(startBtnSlot()));
    connect(pauseBtn,SIGNAL(clicked(bool)),\
            this,SLOT(pauseBtnSlot()));
    connect(fullScreenBtn,SIGNAL(clicked(bool)),\
            this,SLOT(fullScreenBtnSlot()));
    connect(photoBtn,SIGNAL(clicked(bool)),\
            this,SLOT(photoBtnSlot()));
    connect(videoBtn,SIGNAL(clicked(bool)),\
            this,SLOT(videoBtnSlot()));
    connect(stopRecordBtn,SIGNAL(clicked(bool)),\
            this,SLOT(stopRecordBtnSlot()));
    connect(exitBtn,SIGNAL(clicked(bool)),\
            this,SLOT(exitBtnSlot()));
    //设置部分按钮不可点击
    fullScreenBtn->setEnabled(false);
    photoBtn->setEnabled(false);
    videoBtn->setEnabled(false);
}

ShowImage::~ShowImage()
{
    delete startBtn;delete pauseBtn;
    delete fullScreenBtn;delete photoBtn;
    delete videoBtn;delete stopRecordBtn;
    delete exitBtn;
    delete stacked;delete stacked2;
    //结束线程
    if(th!=NULL)
        th->terminate();
}
//给当前页面 增加背景
void ShowImage::brushColor()
{
    //指定 图片加载器 的格式
    image = QImage(480,360,QImage::Format_ARGB32);
    //准备渐变色
    QLinearGradient  linear(0,0,480,360);
    linear.setColorAt(0,QColor("white"));
//    linear.setColorAt(0.5,QColor("blue"));
    linear.setColorAt(1.0,QColor("blue"));
    //
    QPainter  painter(&image);
    painter.setBrush(linear);
    painter.drawRect(0,0,480,360);
    //绘制 中间 图片
    painter.drawImage(QRect(160,90,150,150),\
                     QImage(":/images/bg.png"));

}
//绘制事件
void ShowImage::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter   painter(this);
    QRect  tar(0,0,480,360);
    QRect  src(0,0,image.width(),image.height());
    painter.drawImage(tar,image,src);
    //
    if(net)
    {
        painter.setPen(QColor("yellow"));
        painter.setFont(QFont("Times",17));
        painter.drawText(10,320,ip);
        painter.drawText(10,340,QString::number(port));
    }
}

void ShowImage::startBtnSlot()
{
    stacked->setCurrentIndex(1);
    Dialog  dig;
    dig.exec();
    if(dig.result() == QDialog::Accepted)
    {
        //Yes按钮
        ip = dig.getIP();
        port = dig.getPort();

//        qDebug()<<ip<<port;
        //启动线程
        if(th == NULL)
        {
            th = new MyThread;
            connect(th,SIGNAL(sendImage(QImage)),\
                 this,SLOT(receiveImage(QImage)));
            connect(th,SIGNAL(sendNetSuccess()),\
                    this,SLOT(setBtnEnable()));
        }
        th->setNetwork(ip,port);//配置网络
        th->setStart(true);//设置 标记
        th->start(); //启动线程

    }else{
        //No按钮
        qDebug()<<"just do it !";
        return;
    }
    stopRecordBtn->setEnabled(true);

}

void ShowImage::pauseBtnSlot()
{
    stacked->setCurrentIndex(0);
    if(th!=NULL)
    {
        th->setStart(false);
    }
    fullScreenBtn->setEnabled(false);
    photoBtn->setEnabled(false);
    videoBtn->setEnabled(false);
    /*stopRecordBtn->setIcon(QIcon(":/images/Video.png"));*/
    stopRecordBtn->setEnabled(false);


    net = false;
}

void ShowImage::fullScreenBtnSlot()
{
    FullScreen  full;

    //绑定信号与槽
    connect(th,SIGNAL(sendImage(QImage)),\
            &full,SLOT(receiveImage(QImage)));
    disconnect(th,SIGNAL(sendImage(QImage)),\
            this,SLOT(receiveImage(QImage)));
    full.exec();
    connect(th,SIGNAL(sendImage(QImage)),\
            this,SLOT(receiveImage(QImage)));
}
//截图
void ShowImage::photoBtnSlot()
{
    QString  fileName(QString(QDateTime::currentDateTime().toString("yyyyMMdd")) +"/"+"%1.jpg");
    fileName = fileName.arg\
            (QDateTime::currentDateTime().toString\
             ("yyMMddhhmmsszzz"));
    qDebug()<<fileName;
    image = image.scaled(480,360);
    image.save(fileName,"JPEG");
    QDateTime  datetime;
    QString timestr=datetime.currentDateTime().toString("yyyyMMdd");
    QString fileLog = QString(QDateTime::currentDateTime().toString("yyyyMMdd"))+"/" + timestr + "_log.txt";//假设指定文件夹路径
    qDebug()<<fileLog;
    QFile file(fileLog);
    file.open(QIODevice::WriteOnly | QIODevice::Append );
    QTextStream in(&file);
    in<<"\nfilename = "+fileName.right(19) \
         + "      "+"creatDate = " +QDateTime::currentDateTime().toString("yyyy-MM-dd")+ \
        "  "+"creatTime = "+QString(QDateTime::currentDateTime().toString("hh:mm:ss:zzzz"));

    file.flush();
    file.close();
}

void ShowImage::videoBtnSlot()
{
    stacked2->setCurrentIndex(1);
    //开始录制视频
    th->startRecordVideo(true);

}

void ShowImage::stopRecordBtnSlot()
{
    stacked2->setCurrentIndex(0);
    //结束录制视频
    th->startRecordVideo(false);
    QDateTime time = QDateTime::currentDateTime();
    int timeT =  time.toTime_t();
    qDebug()<<timeT;
    int times = timeT - 259200;
    QDateTime timeX = QDateTime::fromTime_t(times);
    qDebug()<<timeX;

}

void ShowImage::exitBtnSlot()
{
    emit removeGUI(this);
}
//用来接收 线程 发来的 图片
void ShowImage::receiveImage(QImage image)
{
    this->image = image;
    this->update();//刷新界面,触发绘制事件
}
//网络连接成功后，设置部分按钮 可用
void ShowImage::setBtnEnable()
{
   fullScreenBtn->setEnabled(true);
   photoBtn->setEnabled(true);
   videoBtn->setEnabled(true);
   net = true;
}




