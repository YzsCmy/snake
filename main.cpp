#include "mainwindow.h"
#include <QApplication>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include <QTime>
#include <algorithm>
int main(int argc, char *argv[])
try
{


    QApplication app(argc, argv);
    MainWindow w;
    w.show();

    return app.exec();
}
catch( std::exception& e)
{
    qDebug()<<e.what();
}
