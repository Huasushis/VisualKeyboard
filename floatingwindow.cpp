#include "floatingwindow.h"
#include "ui_floatingwindow.h"

FloatingWindow::FloatingWindow(QWidget *parent) :
      QWidget(parent),
      ui(new Ui::FloatingWindow)
{
    ui->setupUi(this);
}

FloatingWindow::~FloatingWindow()
{
    delete ui;
}
