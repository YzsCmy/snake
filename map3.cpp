#include "map3.h"

Map3::Map3(QWidget *parent) :
    QWidget(parent)
{
    //上下墙体
    for(int i=0;i<580;i+=10)
    {
        mapRect.append(QRectF(i,0,10,10));
        mapRect.append(QRectF(i,470,10,10));
    }
    //左右墙体
    for(int i=10;i<480;i+=10)
    {
        mapRect.append(QRectF(0,i,10,10));
        mapRect.append(QRectF(570,i,10,10));
    }

    //特殊墙体

    for(int i=220;i<320;i+=10)
    {
        mapRect.append(QRectF(i,140,10,10));

    }
    for(int i=100;i<200;i+=10)
    {
        mapRect.append(QRectF(i,300,10,10));

    }
    for(int i=350;i<450;i+=10)
    {
        mapRect.append(QRectF(i,300,10,10));

    }
}
