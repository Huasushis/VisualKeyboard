#ifndef DONATE_H
#define DONATE_H

#include <QDialog>

namespace Ui {
class donate;
}

class donate : public QDialog
{
    Q_OBJECT

public:
    explicit donate(QWidget *parent = nullptr);
    ~donate();

private:
    Ui::donate *ui;
};

#endif // DONATE_H
