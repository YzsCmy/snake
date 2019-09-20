#ifndef RANKWIDGET_H
#define RANKWIDGET_H

#include <QWidget>

namespace Ui {
class RankWidget;
}

class RankWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RankWidget(QWidget *parent = 0);
    ~RankWidget();

private:
    Ui::RankWidget *ui;
};

#endif // RANKWIDGET_H
