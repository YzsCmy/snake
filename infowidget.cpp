#include "infowidget.h"
#include "ui_infowidget.h"

InfoWidget::InfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoWidget)
{
    ui->setupUi(this);

    this->move(230,180);
    //设置模态窗口属性
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setWindowModality(Qt::WindowModal);
    connect(ui->pushButton,&QPushButton::clicked,this,&InfoWidget::close);
}

InfoWidget::~InfoWidget()
{
    delete ui;
}
