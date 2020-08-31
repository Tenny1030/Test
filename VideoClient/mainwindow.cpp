#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createScrollArea();
    index = 0;
    X = 10;Y = 10;J = 4;
    //页面初始化
    this->resize(1024,768);
    this->setWindowTitle(tr("视频监控"));
    this->setWindowIcon(QIcon(":/images/bg.png"));
    //创建菜单栏、工具栏
    createMenu();
    createTool();
    //
//    showImage = new ShowImage(this);
//    showImage->setGeometry(10,90,480,360);
    //
    addBtn = new QPushButton("+",w);
    addBtn->setGeometry(X,Y,480,360);
    QFont  font("Times",200);
    font.setBold(true); //设置粗体
    addBtn->setFont(font);
    connect(addBtn,SIGNAL(clicked(bool)),\
            this,SLOT(addSlot()));

}

MainWindow::~MainWindow()
{

}

void MainWindow::createMenu()
{
//    menu_bar = new QMenuBar(this);
    menu_bar = this->menuBar();//产生菜单栏
//    menu_bar->setStyleSheet("background:#BBCCDD");
    //添加菜单
    QMenu *file = menu_bar->addMenu("文件");
    QMenu *back = menu_bar->addMenu("回看");
    QMenu *about = menu_bar->addMenu("关于Qt");
    add = file->addAction(QIcon(":/images/New.png"),"添加");
    quit = file->addAction(QIcon(":/images/Exit.png"),"退出");
    backVideo = back->addAction(QIcon(":/image/New.png"), "回看视频");
    backPhoto = back->addAction(QIcon(":/image/New.png"), "回看照片");
    aboutQt = about->addAction(QIcon(":/images/About.png"),"关于Qt");
    //快捷键
    add->setShortcut(QKeySequence("Ctrl+O"));
    quit->setShortcut(QKeySequence("Ctrl+Q"));

    //绑定信号与槽(QAction)
    connect(add,SIGNAL(triggered(bool)),\
            this,SLOT(addSlot()));
    connect(quit,SIGNAL(triggered(bool)),\
            this,SLOT(quitSlot()));
    connect(backPhoto,SIGNAL(triggered(bool)), \
            this,SLOT(backPhotoSlot()));
    connect(backVideo,SIGNAL(triggered(bool)), \
            this,SLOT(backVideoSlot()));
    connect(aboutQt,SIGNAL(triggered(bool)),\
            this,SLOT(aboutQtSlot()));
}

void MainWindow::createTool()
{
    tool_bar = this->addToolBar("main");
    add = tool_bar->addAction(QIcon(":/images/New.png"),"添加");
    quit = tool_bar->addAction(QIcon(":/images/Exit.png"),"退出");
    //
    connect(add,SIGNAL(triggered(bool)),\
            this,SLOT(addSlot()));
    connect(quit,SIGNAL(triggered(bool)),\
            this,SLOT(quitSlot()));
    //设置 工具栏样式：文字在图片下方
    tool_bar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    //设置工具栏不可移动
    tool_bar->setMovable(false);
    //设置工具栏的背景色(样式表)
//    tool_bar->setStyleSheet("color:white;background:#115544");
    //设置时间
    QString str = QDateTime::\
          currentDateTime().toString\
            ("yyyy年MM月dd日 dddd hh:mm:ss   ");
    timeLabel = new QLabel;
    timeLabel->setFont(QFont("Console",23));
    timeLabel->setText(str);
    //弹簧效果
    QWidget *space = new QWidget;
//    space->setMinimumWidth(300);
    space->setSizePolicy(QSizePolicy::Expanding,\
                         QSizePolicy::Expanding);
    tool_bar->addWidget(space);
    tool_bar->addWidget(timeLabel);
    //
    QTimer *timer = new QTimer;
    connect(timer,SIGNAL(timeout()),\
            this,SLOT(timerSlot()));
    timer->start(1000);
}
//建立滚动条
void MainWindow::createScrollArea()
{
    QScrollArea * scroll = new QScrollArea(this);
    scroll->setBackgroundRole(QPalette::Dark);
    this->setCentralWidget(scroll);//将滚动条添加到“中间区域”
    //
    w = new QWidget(scroll);
    scroll->setWidget(w);//在滚动条上添加 widget
    w->setGeometry(0,0,1920,500);
}
//改变widget的 高度
void MainWindow::changeWidgetSize()
{
    w->resize(1920,(list.size()/J+1)*360);
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter  painter(this);
    painter.drawImage(QRect(0,0,this->width(),\
                            this->height()),imagex);
}



void MainWindow::addSlot()
{
    //获取按钮位置,用来存放即将出现的 ShowImage界面
    QRect r = addBtn->geometry();
    qDebug()<<r;
    //构建ShowImage界面
    ShowImage *sh = new ShowImage(w);
    sh->setGeometry(r);
    sh->show();
    list.append(sh);
    connect(sh,SIGNAL(removeGUI(ShowImage*)),\
            this,SLOT(removeGUISlot(ShowImage*)));

//    X +=480;
    //判断是否需要换行
    if(list.size()%J != 0)
    {
        //没有满一行
        X += 480;
    }else{
        Y += 360;
        X = 10;
    }
    //移动按钮位置
    addBtn->move(X,Y);//..........
    changeWidgetSize();
}

void MainWindow::quitSlot()
{
    this->close();
    QMessageBox::information(this,
                             tr("Farewell"),
                             tr("see you later!"));
}

void MainWindow::backVideoSlot()
{
    QString path = QFileDialog::getOpenFileName(this,
                                                tr("选择录像"),
                                                "",
                                                tr("Videoes (*.avi )"));
   if(path.isEmpty())
   {
       return;
   }
   else
   {
       /*
         playlist = new QMediaPlaylist;
         player = new QMediaPlayer;
         videoWidget = new QVideoWidget;
         setCentralWidget(videoWidget);
         player->setVideoOutput(VideoWidget);
         QFile file(path);
         if(!file.open(QIODevice::ReadOnly))
         {
             QMessageBox::information(this,
                                      tr("打开录像失败"),
                                      tr("打开录像失败!"));
         }
         else
         {
             player->setVideoOutput(VideoWidget);
             player->setMedia(QUrl::fromLocalFile(path));   //这里是播放视频的路径，具体根据实际情况更改
             player->play();
             qDebug()<<"hello world !";
         }

            playlist->addMedia(QUrl::fromLocalFile(path));
            playlist->setCurrentIndex(1);
            player->setPlaylist(playlist);
            player->setVideoOutput(videoWidget);
            videoWidget->show();
            player->play();
            */
         QDesktopServices::openUrl(path);
   }

}

void MainWindow::backPhotoSlot()
{
    QString path = QFileDialog::getOpenFileName(this,
                                                tr("选择图像"),
                                                "",
                                                tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
   if(path.isEmpty())
   {
       return;
   }
   else
   {
      QImage* img=new QImage;
      if(! ( img->load(path) ) ) //加载图像
      {
          QMessageBox::information(this,
                                   tr("打开图像失败"),
                                   tr("打开图像失败!"));
          delete img;
          return;
      }
      else
      {
              /*
              QLabel* label=new QLabel("",0);
              QImage img;
              img.load(path);
              QPixmap mp;
              mp=mp.fromImage(img);
              label->setPixmap(mp);
              label->show();
              */
          QDesktopServices::openUrl(path);

      }
    }

}



void MainWindow::aboutQtSlot()
{
    QMessageBox::aboutQt(this,"aboutQt");
}

void MainWindow::timerSlot()
{
    //设置时间
    QString str = QDateTime::\
          currentDateTime().toString\
            ("yyyy年MM月dd日 dddd hh:mm:ss   ");
    timeLabel->setText(str);
}

void MainWindow::receiveImage(QImage image)
{
    this->imagex = image;
    this->update();
}

void MainWindow::removeGUISlot(ShowImage *show)
{
    //找出当前的 show 是 list中的第几项
    index = list.indexOf(show);
    //将按钮移动到 最后一个子界面的位置
    addBtn->setGeometry(list.last()->geometry());
    //移动界面
    for(int i=list.size()-1;i>index;i--)
    {
        QRect r = list.at(i-1)->geometry();
        list.at(i)->setGeometry(r);
    }
    //
    if(list.size()%J != 0)
    {
        X -= 480;
    }else{
        Y -= 360;
        X = 10+(J-1)*480;//每行的最后一个的X坐标
    }

    list.removeOne(show);
    //删除界面
    delete show;
}





