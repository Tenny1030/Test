#ifndef FULLSCREEN_H
#define FULLSCREEN_H

#include <QWidget>
#include <QDialog>
#include <QPaintEvent>
#include <QPainter>

class FullScreen : public QDialog
{
    Q_OBJECT
public:
    explicit FullScreen(QWidget *parent = 0);
protected:
    void  paintEvent(QPaintEvent *event);
signals:

public slots:
    void receiveImage(QImage image);//
private:
    QImage  image;
};

#endif // FULLSCREEN_H
