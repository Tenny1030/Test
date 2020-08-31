#include "dialog.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent)
{
    this->setFixedSize(360,190);//设置固定大小
    this->setWindowTitle("网络连接");
    //构造控件
    QFont  font("Times",20,1);
    IPLabel = new QLabel("IP:",this);
    IPLabel->setFixedSize(100,45);
    IPLabel->setFont(font);

    IPLine = new QLineEdit("127.0.0.1",this);
    IPLine->setFixedSize(200,40);
    IPLine->setFont(font);
    IPLine->setInputMask("000.000.000.000");

    portLabel = new QLabel("Port:",this);
    portLabel->setFixedSize(100,45);
    portLabel->setFont(font);

    portLine = new QLineEdit("10000",this);
    portLine->setFixedSize(200,40);
    portLine->setFont(font);

    btn = new QDialogButtonBox\
      (QDialogButtonBox::Yes|QDialogButtonBox::No);
    btn->setFont(font);
    //布局管理
    h1 = new QHBoxLayout;
    h1->addWidget(IPLabel);
    h1->addWidget(IPLine);

    h2 = new QHBoxLayout;
    h2->addWidget(portLabel);
    h2->addWidget(portLine);

    h3 = new QHBoxLayout;
    h3->addStretch();
    h3->addWidget(btn);

    v = new QVBoxLayout;
    v->addLayout(h1);
    v->addLayout(h2);
    v->addLayout(h3);

    this->setLayout(v);
    //
    connect(btn,SIGNAL(accepted()),\
            this,SLOT(accept()));
    connect(btn,SIGNAL(rejected()),\
            this,SLOT(reject()));
}

Dialog::~Dialog()
{
//    delete IPLabel;delete IPLine;delete portLabel;
//    delete portLine;delete btn;
//    delete h1;delete h2;delete h3;
//    delete v;
}
//获取IP
QString Dialog::getIP()
{
    return IPLine->text();
}
//获取端口号
int Dialog::getPort()
{
    return portLine->text().toInt();
}







