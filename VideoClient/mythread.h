#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QMainWindow>
#include <QThread>
#include <QTcpSocket>
#include <QImage>
#include <QDateTime>
#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <QFileDialog>
extern  "C"  //以C语言的语法去编译该文件
{
    #include "avilib.h"
}

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);
    void  setNetwork(QString ip,int port);
    void  setStart(bool flag);
    void  startRecordVideo(bool record);
protected:
    void run();
signals:
    void sendImage(QImage);
    void sendNetSuccess();
public slots:
private:
    //QMainWindow win;
    QString ip;
    int   port;
    bool  flag;
    //
    avi_t  *avi; //avi库的接口 结构体指针
    QDir  dir;
    QFile file;
    bool  record;

};

#endif // MYTHREAD_H
