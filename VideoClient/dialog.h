#ifndef DIALOG_H
#define DIALOG_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox> //一组按钮
#include <QHBoxLayout>  //水平布局
#include <QVBoxLayout>  //垂直布局

class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    QString  getIP();
    int  getPort();
signals:

public slots:
private:
    QLabel  *IPLabel;
    QLabel  *portLabel;
    QLineEdit  *IPLine;
    QLineEdit  *portLine;
    QDialogButtonBox  *btn;
    QHBoxLayout  *h1;
    QHBoxLayout  *h2;
    QHBoxLayout  *h3;
    QVBoxLayout  *v;
};

#endif // DIALOG_H
