#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QTimer>
#include <QList>
#include <QDebug>
#include <QTime>
#include <QKeyEvent>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QFileInfo>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include <QTime>
#include <QRectF>
#include "mainwindow.h"
#include <QMessageBox>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QString str = QString("<html><head/><body><p><span style=\"font-size:12pt;\">%1</span><br/></p></body></html>").arg(score);
    ui->score_label->setText(str);

    mapRect = Map1(this).mapRect;
    snake.append(QRectF(100,50,snakeNodeWidth,snakeNodeHeight));
    addRightRectF();
    addRightRectF();
    //首先生成一个食物
    QPointF point = x_notin_block();
    rewardNode.append(QRectF(point.x(),point.y(),snakeNodeWidth,snakeNodeWidth));


    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&Widget::timeOut);

    init_btn_connect();

}
//绘图
void Widget::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    QPen pen;
    QBrush brush(Qt::black);


    //绘制屏幕背景

    painter.setBrush(brush);
    painter.drawRect(QRect(0,0,580,480));

    painter.setRenderHint(QPainter::Antialiasing, true);
    // 设置画笔颜色、宽度
    painter.setPen(QPen(QColor(180, 211, 200,100), 3));
    // 设置画刷颜色
    painter.setBrush(QColor(150, 150, 150));

    //绘制墙体
    for(int i=0; i<mapRect.length(); i++){
        painter.drawRect(mapRect.at(i));
    }

    pen.setColor(Qt::black);
    brush.setColor(Qt::green);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.setPen(pen);
    //绘制蛇
    for(int i=0; i<snake.size(); i++){
        painter.drawRect(snake.at(i));
    }
    brush.setColor(Qt::red);
    //绘制食物
    painter.setBrush(brush);
    for(int i=0; i<rewardNode.length(); i++){
        painter.drawEllipse(rewardNode.at(i));
    }



    //TODO判断地图、蛇是否重叠
    if(!snake_notin_wall() && !flags ){
        flags = true;
        timer->stop();
        gameOver = true;
        //TODO 游戏结束，保存数据，弹出提示框，返回主界面
        infow = new InfoWidget(this);
        infow->show();

    }
    //判断蛇是否吃到自己
    if(snakeStrike() && !flags){
        flags = true;
        timer->stop();
        gameOver = true;
        //TODO 游戏结束，保存数据，弹出提示框，返回主界面
        infow = new InfoWidget(this);
        infow->show();
    }

    QWidget::paintEvent(event);
}


//向上移动
void Widget::addTopRectF()
{
    if(snake.at(0).y()-snakeNodeHeight < 0){
        snake.insert(0,QRectF(QPointF(snake.at(0).x(),this->height()-snakeNodeHeight),
                              QPointF(snake.at(0).x()+snakeNodeWidth,this->height())));
    }else{
        snake.insert(0,QRectF(snake.at(0).topLeft()+QPointF(0,-snakeNodeHeight),snake.at(0).topRight()));
    }
}
//向下移动
void Widget::addDownRectF()
{
    if(snake.at(0).y()+snakeNodeHeight*2 > this->height()){
        snake.insert(0,QRectF(QPointF(snake.at(0).x(),snakeNodeHeight),
                              QPointF(snake.at(0).x()+snakeNodeWidth,0)));
    }else{
        snake.insert(0,QRectF(snake.at(0).bottomLeft(),snake.at(0).bottomRight()+QPointF(0,snakeNodeHeight)));
    }
}
//向左移动
void Widget::addLeftRectF()
{
    if(snake.at(0).x()-snakeNodeWidth < 0){
        snake.insert(0,QRectF(QPointF(580-snakeNodeWidth,snake.at(0).y()),
                              QPointF(580,snake.at(0).y()+snakeNodeHeight)));
    }else{
        snake.insert(0,QRectF(snake.at(0).topLeft()+QPointF(-snakeNodeWidth,0),snake.at(0).bottomLeft()));
    }
}
//向右移动
void Widget::addRightRectF()
{
    if(snake.at(0).x()+snakeNodeWidth*2 > this->width()){
        snake.insert(0,QRectF(QPointF(0,snake.at(0).y()),
                              QPointF(snakeNodeWidth,snake.at(0).y()+snakeNodeHeight)));
    }else{
        snake.insert(0,QRectF(snake.at(0).topRight(),snake.at(0).bottomRight()+QPointF(snakeNodeWidth,0)));
    }
}
//删除结尾数据
void Widget::deleteLastRectF()
{
    snake.removeLast();
}


//移动蛇
void Widget::timeOut()
{
    if(rewardNode.at(0).contains(snake.at(0).topLeft()+QPointF(snakeNodeWidth/2,snakeNodeHeight/2))){

        addscore();
        rewardNode.removeAt(0);
        rewardTimeOut();
        switch (moveFlage) {
            case Up:
                addTopRectF();
                break;
            case Down:
                addDownRectF();
                break;
            case Right:
                addRightRectF();
                break;
            case Left:
                addLeftRectF();
                break;
            default:
                break;
        }
    }else{
        switch (moveFlage) {
            case Up:
                addTopRectF();
                break;
            case Down:
                addDownRectF();
                break;
            case Right:
                addRightRectF();
                break;
            case Left:
                addLeftRectF();
                break;
            default:
                break;
            }
        deleteLastRectF();
    }

    update();
}

void Widget::rewardTimeOut()
{
    QPointF point = x_notin_block();

    rewardNode.append(QRectF(point.x(),point.y(),snakeNodeWidth,snakeNodeWidth));
}




void Widget::setMap(QString smap)
{
    mapstr = smap;
    if(smap.compare("map1")==0){
        QList<QRectF> map1 =  Map1(this).mapRect;
        mapRect = map1;
    }else if (smap.compare("map2")==0) {
        mapRect =  Map2(this).mapRect;
    }else if (smap.compare("map3")==0) {
        mapRect =  Map3(this).mapRect;
    }
}

bool Widget::snakeStrike()
{
    for(int i=0; i<snake.length(); i++){
        for(int j=i+1; j<snake.length(); j++){
            if(snake.at(i) == snake.at(j)){
                return true;
            }
        }
    }
    return false;

}

QPointF Widget::x_notin_block()
{
    bool flag = false;
    qsrand(QTime::currentTime().msec());
    int cx;
    int cy;
    while(true){
        cx = (qrand()%(550/20)*20)+10;
        cy = (qrand()%(460/20)*20)+10;
        for(int i=0;i<mapRect.length();i++){
            if(mapRect.at(i).left()==cx&&mapRect.at(i).top()==cy){
                flag = true;
                break;
            }
        }
        if(flag){
            flag = false;
            continue;
        }
        for(int i=0;i<snake.length();i++){
            if(snake.at(i).left()==cx&&snake.at(i).top()==cy){
                flag = true;
                break;
            }
        }
        if(flag){
            flag = false;
            continue;
        }
        if(!flag){
            break;
        }
    }
    return QPoint(cx,cy);
}
bool Widget::snake_notin_wall()
{
    for(int i=0;i<mapRect.length();i++)
    {
        if(mapRect.contains(snake.at(0))){
            return false;
        }

    }
    return true;
}

void Widget::addscore()
{
   score+=5;
   QString str = QString("<html><head/><body><p><span style=\"font-size:12pt;\">%1</span><br/></p></body></html>").arg(score);
   ui->score_label->setText(str);
}

void Widget::init_btn_connect()
{
    //退出
    connect(ui->exit_btn,&QPushButton::clicked,this,[=](){
        if(gameStart){
            if(gameOver){
                timer->stop();
                save_rank_data();
                //不保存游戏数据,删除文件game.data
                if(QFile::exists("./game.data")){
                    QFile::remove("./game.data");
                }
            }else {
                timer->stop();
                gameOver = true;
                //保存游戏数据
                savedata();
            }
        }else {
            //保存游戏数据
            savedata();

        }
//        mainwidget->close();
        this->close();

    });

    //返回主界面
    connect(ui->save_exit_btn,&QPushButton::clicked,this,[=](){
        if(gameStart){
            if(gameOver){
                timer->stop();
                save_rank_data();
                qDebug()<<"befor delete btn"<<endl;
                //不保存游戏数据,删除文件game.data
                if(QFile::exists("./game.data")){
                    qDebug()<<"befor remove file"<<endl;
                    QFile::remove("./game.data");
                }
//                mainwidget->deletBtn();
                qDebug()<<"delete btn"<<endl;
            }else {
                timer->stop();
                gameOver = true;
                //保存游戏数据
                savedata();
            }
        }else {

            //保存游戏数据
            savedata();

        }

        mainwidget = new MainWindow;
        mainwidget->show();
//        mainwidget->reload();
        this->close();

    });

    //点击向上按钮
    connect(ui->up_btn,&QPushButton::clicked,this,[=](){
        if(moveFlage != Down&&!gameOver){
            moveFlage = Up;
        }
    });
    //点击向下按钮
    connect(ui->down_btn,&QPushButton::clicked,this,[=](){
        if(moveFlage != Up&&!gameOver){
            moveFlage = Down;
        }
    });
    //点击向左按钮
    connect(ui->left_btn,&QPushButton::clicked,this,[=](){
        if(moveFlage != Right&&!gameOver){
            moveFlage = Left;
        }
    });
    //点击向右按钮
    connect(ui->right_btn,&QPushButton::clicked,this,[=](){
        if(moveFlage != Left&&!gameOver){
            moveFlage = Right;
        }
    });
    //点击暂停按钮
    connect(ui->stop_btn,&QPushButton::clicked,this,[=](){
        if(gameStart && !gameOver){
            timer->stop();
            gameStart = false;
            ui->stop_btn->setText("开始");
        }else if(!gameStart && !gameOver){
            timer->start(time);
            gameStart = true;
            ui->stop_btn->setText("暂停");
        }
    });

}

void Widget::setScoreSTr(QString str)
{
     ui->score_label->setText(str);
}

void Widget::setSnakeList(QList<QRectF> snakelist)
{
    snake.clear();
    snake.clear();
    snake = snakelist;
}

void Widget::setFood(QPointF point)
{
    rewardNode.clear();
    rewardNode.append(QRectF(point.x(),point.y(),10,10));
}



//保存上一次游戏数据
void Widget::savedata()
{

    QJsonArray array;
    for(int i=0;i<snake.size();i++){
        QJsonObject obj1;
        obj1.insert("x", snake.at(i).topLeft().x());
        obj1.insert("y", snake.at(i).topLeft().y());
        array.push_back(obj1);
    }
    QJsonObject levelobj;
    QJsonObject dirobj;
    QJsonObject mapobj;
    QJsonObject scoreobj;
    QJsonObject foodobj;
    if(rewardNode.size()==0){
        QPointF pointf = x_notin_block();
        foodobj.insert("x",pointf.x());
        foodobj.insert("y",pointf.y());
    }else {
        foodobj.insert("x",rewardNode.at(0).topLeft().x());
        foodobj.insert("y",rewardNode.at(0).topLeft().y());
    }

    int i=5;
    if(moveFlage==Up){
        i=1;
    }

    if(moveFlage==Down){
        i=2;
    }

    if(moveFlage==Left){
        i=3;

    }

    if(moveFlage==Right){
        i=4;

    }
    levelobj.insert("level",level);
    dirobj.insert("dir",i);
    mapobj.insert("map", mapstr);
    scoreobj.insert("score", score);

    array.push_back(levelobj);
    array.push_back(dirobj);
    array.push_back(foodobj);
    array.push_back(mapobj);
    array.push_back(scoreobj);
//    写入文件

    QJsonDocument jsonDoc(array);
    QByteArray ba = jsonDoc.toJson();
    QFile file("game.data");
    if(!file.open(QIODevice::ReadWrite|QIODevice::Truncate))
    {
       qDebug() << "write json file failed";
    }
    file.write(ba);

    file.close();
}


void Widget::save_rank_data()
{
    //读取文件
    QFile file("rank.data");
    if(!file.exists()){
        int scorearr[1];
        scorearr[0]=score;
//      写入数据
        if(!file.open(QIODevice::WriteOnly))
        {
           qDebug() << "write json file failed3";
        }

        file.write(QString::number(scorearr[0]).toUtf8());
        file.close();
    }else {
        if(!file.open(QIODevice::ReadWrite))
        {
           qDebug() << "write json file failed1";
        }

        QString scorestr(file.readAll());
        QStringList strlist = scorestr.split("\n");
        strlist.append(QString::number(score));
        int scorearr[strlist.size()];
        for(int i=0;i<strlist.size();i++){
            scorearr[i] = strlist.at(i).toInt();
        }

        file.close();
        //排序
        std::sort(scorearr,scorearr+strlist.size(),[](int a, int b){ return a>b;});

        //清空文件内容
        file.resize(0);
//      写入数据
        if(!file.open(QIODevice::WriteOnly))
        {
           qDebug() << "write json file failed3";
        }

        for(int j=0;j<strlist.size()-1;j++){
            file.write(QString::number(scorearr[j]).append("\n").toUtf8());
        }
        file.write(QString::number(scorearr[strlist.size()-1]).toUtf8());
        file.close();
    }
}

//设置难度等级
void Widget::setLevel(QString levelstr)
{

    if(levelstr.compare("1")==0){
        level = 1;
        time = 500;
    }else if (levelstr.compare("2")==0) {
        level = 2;
        time = 300;
    }else if(levelstr.compare("3")==0){
        level = 3;
        time = 100;
    }
}

void Widget::setDirection(QString dir)
{
    if(dir.compare("1")==0){
        moveFlage = Up;
    }else if (dir.compare("2")==0) {
        moveFlage = Down;
    }else if(dir.compare("3")==0){
        moveFlage = Left;
    }else if(dir.compare("4")==0){
        moveFlage = Right;
    }
}

Widget::~Widget()
{
    delete ui;
}
