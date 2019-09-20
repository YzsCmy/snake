#include "map1.h"

Map1::Map1(QWidget *parent) :
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
    for(int i=240;i<340;i+=10)
    {
        mapRect.append(QRectF(i,240,10,10));
    }
}
