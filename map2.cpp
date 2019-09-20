#include "map2.h"

Map2::Map2(QWidget *parent) :
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
    for(int i=190;i<290;i+=10)
    {
        mapRect.append(QRectF(200,i,10,10));
        mapRect.append(QRectF(380,i,10,10));
    }
}
