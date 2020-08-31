#-------------------------------------------------
#
# Project created by QtCreator 2017-10-09T14:05:06
#
#-------------------------------------------------

QT       += core gui network  multimedia\
            multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    showimage.cpp \
    mybutton.cpp \
    dialog.cpp \
    fullscreen.cpp \
    mythread.cpp \
    avilib.c \
    mywidget.cpp


HEADERS  += mainwindow.h \
    showimage.h \
    mybutton.h \
    dialog.h \
    fullscreen.h \
    mythread.h \
    avilib.h \
    mywidget.h

RESOURCES += \
    icons.qrc
