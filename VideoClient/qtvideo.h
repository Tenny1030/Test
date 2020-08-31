#ifndef QTVIDEO_H
#define QTVIDEO_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QUrl>

class qtvideo : public QMainWindow
{
    Q_OBJECT
public:
    QMediaPlaylist * playlist;
    QMediaPlayer * player;
    QVideoWidget * videoWidget;
    explicit qtvideo(QWidget *parent = 0);
    ~qtvideo();

signals:

public slots:
};

#endif // QTVIDEO_H
