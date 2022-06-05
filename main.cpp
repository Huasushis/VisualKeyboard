#include "mainwindow.h"

#include <QApplication>
#include "reg.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowFlags(w.windowFlags() &~ Qt::WindowMaximizeButtonHint);
    w.show();
    return a.exec();
}
