#ifndef CHOOSE_H
#define CHOOSE_H
#include "widget.h"
#include <QWidget>


namespace Ui {
class choose;
}

class choose : public QWidget
{
    Q_OBJECT

public:
    explicit choose(QWidget *parent = 0);
    ~choose();
    void setmapstr();
    void setmainwidget(MainWindow* wind);
    void setlevel();

private:
    Ui::choose *ui;
    Widget *playwidget;

private:
    MainWindow* mianwidget=NULL;
    QString mapstr;
    QString level;
};

#endif // CHOOSE_H
