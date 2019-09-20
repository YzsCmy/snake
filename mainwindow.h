#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "rankwidget.h"
#include "choose.h"
#include <QMainWindow>
#include "widget.h"
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void save_rank();

//    void reload();

public:
    choose * chooseWidget;
    RankWidget *rankWidget;
    Widget * playWidget=NULL;
    QPushButton *continueBtn=NULL;

private:
    Ui::MainWindow *ui;

    int score;
    QString dir;
    QString level;
    QString mapstr;
    QPointF foodP;
    QList<QRectF> snakelist;
    bool connFlag=false;

private:
//    void init_data();



public slots:
    void onstart_click();
    void onrank_click();
    void deletBtn();
};

#endif // MAINWINDOW_H
