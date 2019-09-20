#-------------------------------------------------
#
# Project created by QtCreator 2019-07-10T16:32:33
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = snake
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    choose.cpp \
    rankwidget.cpp \
    map1.cpp \
    map2.cpp \
    map3.cpp \
    widget.cpp \
    infowidget.cpp

HEADERS  += \
    mainwindow.h \
    choose.h \
    rankwidget.h \
    map1.h \
    map2.h \
    map3.h \
    widget.h \
    infowidget.h

FORMS    += mainwindow.ui \
    choose.ui \
    rankwidget.ui \
    widget.ui \
    infowidget.ui

RESOURCES += \
    res.qrc
