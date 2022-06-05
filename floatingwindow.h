#ifndef FLOATINGWINDOW_H
#define FLOATINGWINDOW_H

#include <QWidget>
#include <QMouseEvent>
#include <QColor>
#include <QPainter>
#include <QBitmap>
#include <string>
#include <algorithm>
#include "listenkeyboard.h"
#include <ctime>
#include <QFont>
#include <QFontMetrics>
#include <QTimer>
#include <QRect>
#define AnimationTime 201

using namespace std;
class QPropertyAnimation;

namespace Ui {
class FloatingWindow;
}

class FloatingWindow : public QWidget
{
    Q_OBJECT

public:
    explicit FloatingWindow(QWidget *parent = nullptr);
    ~FloatingWindow();
    QColor bgc;
    void setWdc(QColor wdc);
    void update();
    void updatekey();
    void updatethread();

private:
    Ui::FloatingWindow *ui;
    QPoint pos;
    void paintEvent(QPaintEvent *event);
    QPropertyAnimation *animation;
    QTimer *tim;
    string nows,pres;
    list<int> keys;
    ListenKeyboard lk;
    bool insc(int v);
    bool inst(int v);
    bool prestiky,pretext;
    string vkvalue[600];
    void vkinit();
    clock_t LastUpdateTime;


protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);


private slots:
    void showEvent(QShowEvent *event);
    void closeEvent(QCloseEvent *event);
    void caslot();
    void Ontimeover();
};

#endif // FLOATINGWINDOW_H
