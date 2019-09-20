#ifndef MAP1_H
#define MAP1_H

#include <QWidget>

class Map1 : public QWidget
{
    Q_OBJECT
public:
    QList<QRectF> mapRect;
    explicit Map1(QWidget *parent = 0);

signals:

public slots:

};

#endif // MAP1_H
