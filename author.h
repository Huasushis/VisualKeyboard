#ifndef AUTHOR_H
#define AUTHOR_H

#include <QDialog>

namespace Ui {
class author;
}

class author : public QDialog
{
    Q_OBJECT

public:
    explicit author(QWidget *parent = nullptr);
    ~author();

private:
    Ui::author *ui;
};

#endif // AUTHOR_H
