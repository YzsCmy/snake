#ifndef MAP2_H
#define MAP2_H

#include <QWidget>

class Map2 : public QWidget
{
    Q_OBJECT
public:
    explicit Map2(QWidget *parent = 0);
    QList<QRectF> mapRect;

signals:

public slots:

};

#endif // MAP2_H
