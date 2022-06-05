#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSystemTrayIcon>

#include "reg.h"
#include "donate.h"
#include "author.h"
#include "floatingwindow.h"
#include <QTimer>
#define defaultPosx "243"
#define defaultPosy "864"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_autoStart_stateChanged(int arg1);

    void on_startShow_stateChanged(int arg1);

    void on_donate_triggered();

    void on_author_triggered();

    void iconActivated(QSystemTrayIcon::ActivationReason reason);

    void hideEvent(QHideEvent *event);

    void closeEvent(QCloseEvent *event);

    void on_mess_stateChanged(int arg1);

    void on_bgColor_clicked();

    void on_wdColor_clicked();

    void on_lineEditx_editingFinished();

    void on_lineEdity_editingFinished();

    void on_defaultPos_clicked();

    void on_CurrentPos_doubleclicked();

private:
    Ui::MainWindow *ui;
    Reg regi;
    QColor bgc, wdc;
    bool is_show_message;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    QAction *minimizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    FloatingWindow *fwin;
    QTimer *tim,*tim2;
    ListenKeyboard lktmp;

public slots:
    void exShowNormal();
    void OnTimeOut();
    void OnTest();

};
#endif // MAINWINDOW_H
