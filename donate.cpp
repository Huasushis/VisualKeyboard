#include "donate.h"
#include "ui_donate.h"

donate::donate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::donate)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());
}

donate::~donate()
{
    delete ui;
}
