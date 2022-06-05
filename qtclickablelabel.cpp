#include "qtclickablelabel.h"
QtClickableLabel::QtClickableLabel(const QString &text, QWidget *parent)
    : QLabel(parent)
{
    this->setText(text);
}
QtClickableLabel::QtClickableLabel(QWidget *parent)
    : QLabel(parent)
{
}
QtClickableLabel::~QtClickableLabel()
{
}
void QtClickableLabel::mouseDoubleClickEvent(QMouseEvent *event) {
    emit doubleclicked();
}
void QtClickableLabel::mousePressEvent(QMouseEvent *event) {
    emit clicked();
}
