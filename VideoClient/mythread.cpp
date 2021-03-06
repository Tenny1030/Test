#include "mythread.h"
#include <QDebug>

MyThread::MyThread(QObject *parent) : QThread(parent)
{
    this->flag = false;
    this->record = false;
    avi = NULL;
}
//设置 网络参数
void MyThread::setNetwork(QString ip, int port)
{
    this->ip = ip;
    this->port = port;
}
//控制是否接收数据
void MyThread::setStart(bool flag)
{
    this->flag = flag;
}
//控制 开始和结束 视频录制
void MyThread::startRecordVideo(bool record)
{
    if(record)
    {
        QString fileName(QString(QDateTime::currentDateTime().toString("yyyyMMdd")) +"/"+"%1.avi");
        fileName = fileName.arg\
             (QDateTime::currentDateTime()\
              .toString("yyyy-MM-dd:hh:mm:ss"));

        QString dstPath = QString("/:/home/blackwatch/build-VideoClient-Desktop_Qt_5_4_1_GCC_64bit-Debug/");

        dir.cd(dstPath);
        if(!dir.exists(QDateTime::currentDateTime().toString("yyyyMMdd")))//判断需要创建的文件夹是否存在
        {
            dir.mkdir(QDateTime::currentDateTime().toString("yyyyMMdd")); //创建文件夹
        }
        /*
        QFile filex(fileName);
        if (!filex.open(QIODevice::ReadOnly))
        {
            qDebug()<<"error!";
        }
            qDebug() << file.size();
            filex.close();
            */
        QDateTime  datetime;
        QString timestr=datetime.currentDateTime().toString("yyyyMMdd");
        QString fileLog = QString(QDateTime::currentDateTime().toString("yyyyMMdd"))+"/" + timestr + "_log.txt";//假设指定文件夹路径为D盘根目录
        qDebug()<<fileLog;
        QFile file(fileLog);
        file.open(QIODevice::WriteOnly | QIODevice::Append );
        QTextStream in(&file);
        in<<"\nfilename = "+QString(QDateTime::currentDateTime()\
                                  .toString("yyyy-MM-dd hh:mm:ss"))\
            +".avi" + "  "+"creatDate = " +QDateTime::currentDateTime().toString("yyyy-MM-dd")+ \
            "  "+"creatTime = "+QString(QDateTime::currentDateTime().toString("hh:mm:ss"));

        file.flush();
        file.close();




        //初始化视频输出文件
        avi = AVI_open_output_file(fileName.toUtf8().data());//打开视频流文件
        if(NULL == avi)
        {
            qDebug()<<"open file error";
        }
        AVI_set_video(avi,640,480,9,(char*)"MJPG");//设置视频流格式
    }else{
        if(avi)
        {
            AVI_close(avi);//关闭视频文件
            avi = NULL;
        }
    }
    this->record = record;
}
//新线程
void MyThread::run()
{
    //搭建网路
    QByteArray  dataStream; //用来接收视频流
    QByteArray  frame;  //用来保存一张图片信息
    QTcpSocket  socket;  //套接字，局部变量
    socket.connectToHost(ip,port);//请求连接服务器
    if(socket.waitForConnected())
    {
        //连接成功....
    }else{

        //网络未连接 或者 服务器不存在
        qDebug()<<"32:服务器不存在...";

        /*
        while(1)
        {
          QMessageBox::information(&win,
                                 tr("打开录像失败"),
                                 tr("打开录像失败!"));
        }
        */

        return;
    }
    qDebug()<<"35";
    //给服务器发送 请求视频的 信息
    QByteArray  req;
    req.append("?action=stream\n"); //HTTP请求信息
    socket.write(req); //发送给服务器
    if(socket.waitForBytesWritten(1000))
    {
        //请求信息发送成功
    }else{
        //请求信息发送失败
        qDebug()<<"44：请求信息发送失败";

        return;
    }
    //接收服务器回复的视频数据(报头)
    while(!dataStream.contains("\r\n\r\n"))
    {
        if(socket.waitForReadyRead())//判断是否需要读取
        {
            dataStream.append(socket.readAll());
        }
    }
    //发送网络连接成功的信号
    emit  sendNetSuccess();
    //
    dataStream.remove\
          (0,dataStream.indexOf("\r\n\r\n")+4);//删除报头信息
    //继续接收 视频流  提取图片
    while(flag)
    {
        //读取若干个帧头和图片
        while(!dataStream.contains("\r\n--"))
        {
            if(socket.waitForReadyRead())
            {
                dataStream.append(socket.readAll());
            }
        }
        //提取图片
        dataStream.remove\
              (0,dataStream.indexOf("\n\n")+2);//删除帧头
        frame = dataStream.mid\
              (0,dataStream.indexOf("\r\n--"));//提取一张完整的图片
        //将frame转换成image
        QImage image;
        image.loadFromData(frame,"JPEG");
        //将图片信息发送给 ShowImage
        emit sendImage(image);
        //删除已经提取过得图片
        dataStream.remove(0,frame.size()+4);
        //向视频文件中插入 图片
        if(record)
        {
            if(AVI_write_frame(avi,frame.data(),frame.size(),0)<0)
            {
                qDebug()<<"write erro";
            }
        }
    }
    QImage image;
    image.load(":/images/bg2.PNG");
    emit sendImage(image);
}






