#ifndef MAP3_H
#define MAP3_H

#include <QWidget>

class Map3 : public QWidget
{
    Q_OBJECT
public:
    explicit Map3(QWidget *parent = 0);
    QList<QRectF> mapRect;

signals:

public slots:

};

#endif // MAP3_H
