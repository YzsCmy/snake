#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置背景为黑色
    QPalette palette;
    setAutoFillBackground(true);
    palette.setColor(QPalette::Background, Qt::black);
    this->setPalette(palette);


    //TODO 根据是否存在文件game.data，动态添加"继续游戏"按钮
    QFile file("game.data");
    if(file.exists()){


        snakelist.clear();
        //添加"继续游戏"按钮
        if(continueBtn==NULL){

            continueBtn = new QPushButton("继续游戏",this);
            continueBtn->resize(93,28);
            continueBtn->move(350,150);
        }
        //读取文件，封装数据
        QFile file("game.data");
        if(!file.open(QIODevice::ReadOnly))
        {
            qDebug() << "read json file failed";
        }
        QByteArray ba = file.readAll();
        QJsonParseError e;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(ba, &e);
        QJsonArray jsonarry = jsonDoc.array();

        //封装蛇
        for(int i=0;i<jsonarry.size()-5;i++){

            int cx = jsonarry.at(i).toObject().value("x").toInt();
            int cy = jsonarry.at(i).toObject().value("y").toInt();
            QRectF rec(cx,cy,10,10);
            snakelist.append(rec);
        }
        //封装难度等级
        level = QString::number(jsonarry.at(jsonarry.size()-5).toObject().value("level").toInt());
        //封装方向
        dir = QString::number(jsonarry.at(jsonarry.size()-4).toObject().value("dir").toInt());

        //封装食物
        foodP.setX(jsonarry.at(jsonarry.size()-3).toObject().value("x").toInt());
        foodP.setY(jsonarry.at(jsonarry.size()-3).toObject().value("y").toInt());

        //封装地图
         mapstr = QString(jsonarry.at(jsonarry.size()-2).toObject().value("map").toString());
        //封装得分
        score = jsonarry.at(jsonarry.size()-1).toObject().value("score").toInt();

        if(!connFlag){
            if(continueBtn!=NULL){
                connect(continueBtn,&QPushButton::clicked,this,[=](){
                    playWidget = new Widget;
                    playWidget->score=score;
                    playWidget->setDirection(dir);
                    playWidget->setLevel(level);
                    QString str = QString("<html><head/><body><p><span style=\"font-size:12pt;\">%1</span><br/></p></body></html>").arg(score);
                    playWidget->setScoreSTr(str);
                    playWidget->setSnakeList(snakelist);
                    playWidget->setMap(mapstr);
                    playWidget->setFood(foodP);
                    playWidget->show();
                    this->close();
                });
                connFlag = true;
            }
        }

    }else{
        continueBtn=NULL;
    }

    connect(ui->startButton,&QPushButton::clicked,this,&MainWindow::onstart_click);
    connect(ui->scoreButton,&QPushButton::clicked,this,&MainWindow::onrank_click);

    connect(ui->endButto,&QPushButton::clicked,this,[=](){
        this->close();
    });

}


void MainWindow::onstart_click()
{
    chooseWidget = new choose;
    chooseWidget->setmainwidget(this);
    chooseWidget->show();
}


void MainWindow::onrank_click()
{
    rankWidget = new RankWidget(this);
    rankWidget->show();
}


void MainWindow::deletBtn()
{
    if(continueBtn!=NULL){
        qDebug()<<"in delete btn"<<endl;
        continueBtn->hide();
    }
}

void MainWindow::save_rank()
{

    //读取文件
    QFile rankfile("rank.data");
    QFile gamefile("game.data");
    if(!gamefile.exists()){
        //game.data不存在

        //
    }else if(!rankfile.exists()){
        //game.data存在,rank.data不存在
        int scorearr[1];
        scorearr[0]=score;
//      写入数据
        if(!rankfile.open(QIODevice::WriteOnly))
        {
           qDebug() << "write json file failed3";
        }

        rankfile.write(QString::number(scorearr[0]).toUtf8());
        rankfile.close();


    }else{
        //game.data存在,rank.data存在
        if(!rankfile.open(QIODevice::ReadWrite))
        {
           qDebug() << "write json file failed1";
        }

        QString scorestr(rankfile.readAll());
        QStringList strlist = scorestr.split("\n");
        strlist.append(QString::number(score));
        int scorearr[strlist.size()];
        for(int i=0;i<strlist.size();i++){
            scorearr[i] = strlist.at(i).toInt();
        }

        rankfile.close();
        //排序
        std::sort(scorearr,scorearr+strlist.size(),[](int a, int b){ return a>b;});

        //清空文件内容
        rankfile.resize(0);
//      写入数据
        if(!rankfile.open(QIODevice::WriteOnly))
        {
           qDebug() << "write json file failed3";
        }

        for(int j=0;j<strlist.size()-1;j++){
            rankfile.write(QString::number(scorearr[j]).append("\n").toUtf8());
        }
        rankfile.write(QString::number(scorearr[strlist.size()-1]).toUtf8());
        rankfile.close();

    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
