#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QMessageBox>
#include <QDateTime>
#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include <QList>
#include <QScrollArea>
#include <QFileDialog>
#include <QPixmap>
#include <QLabel>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QUrl>
#include <QDesktopServices>
#include "showimage.h"
#include "mywidget.h"
#include "mythread.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createMenu();//创建菜单栏
    void createTool();//创建工具栏
    void createScrollArea(); //建立滚动条
    void changeWidgetSize();//改变widget的大小
    QMediaPlaylist * playlist;
    QMediaPlayer * player;
    QVideoWidget * videoWidget;
signals:
    void sendImage(QImage);
protected:
     void  paintEvent(QPaintEvent *e);
public slots:
    void addSlot();
    void quitSlot();
    void backVideoSlot();
    void backPhotoSlot();
    void aboutQtSlot();
    void timerSlot();
    void receiveImage(QImage);
    void removeGUISlot(ShowImage *show);
private:
    QImage    imagex;
    QMenuBar *menu_bar;
    QToolBar *tool_bar;
    QAction  *add;
    QAction  *quit;
    QAction  *backVideo;
    QAction  *backPhoto;
    QAction  *aboutQt;
    QLabel  *timeLabel;
    QPushButton  *addBtn; //添加 子页面 按钮

    QList<ShowImage*> list;//存储 子页面 的指针 链表
//    ShowImage  *showImage;
    int index;

    int X;
    int Y;
    int J; //一行有几个子页面

    QWidget  *w;
    int imageW;
    int imageH;
};

#endif // MAINWINDOW_H
