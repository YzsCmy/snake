#include "choose.h"
#include "ui_choose.h"
#include "mainwindow.h"
choose::choose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::choose)
{

    ui->setupUi(this);
    ui->map1Rb->setChecked(true);
    ui->easyRb->setChecked(true);
    connect(ui->retBtn,&QPushButton::clicked,this,[=](){
        mianwidget->close();
        MainWindow* mwidget = new MainWindow;
        mwidget->show();
        this->close();
    });
    connect(ui->startbtn,&QPushButton::clicked,this,[&](){


        if(mianwidget!=NULL&&mianwidget->continueBtn!=NULL){
            mianwidget->save_rank();
        }
        mianwidget->close();
        setmapstr();
        setlevel();
        //创建游戏页面
        playwidget = new Widget;
        //设置地图
        playwidget->setMap(mapstr);
        //设置难度
        playwidget->setLevel(level);
        playwidget->show();
        this->close();
    });
}


void choose::setmapstr()
{

    if(ui->map1Rb->isChecked()){

        mapstr = QString("map1");
    }else if(ui->map2Rb->isChecked()){
        mapstr = QString("map2");

    }else if(ui->map3Rb->isChecked()){
        mapstr = QString("map3");

    }

}

void choose::setlevel()
{

    if(ui->easyRb->isChecked()){
        level = QString("1");
    }else if (ui->medRb->isChecked()) {
        level = QString("2");

    }else if (ui->hardRb->isChecked()) {
        level = QString("3");

    }
}
void choose::setmainwidget(MainWindow* wind)
{
    mianwidget = wind;
}

choose::~choose()
{
    delete ui;
}
