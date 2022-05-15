#ifndef FLOATINGWINDOW_H
#define FLOATINGWINDOW_H

#include <QWidget>

namespace Ui {
class FloatingWindow;
}

class FloatingWindow : public QWidget
{
    Q_OBJECT

public:
    explicit FloatingWindow(QWidget *parent = nullptr);
    ~FloatingWindow();

private:
    Ui::FloatingWindow *ui;
};

#endif // FLOATINGWINDOW_H
