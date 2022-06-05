#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QHideEvent"
#include "QCloseEvent"

#include <QColorDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());

    tim=new QTimer();
    tim2=new QTimer();
    tim2->setInterval(1);
    tim->setInterval(5000);
    connect(tim,SIGNAL(timeout()),this,SLOT(OnTimeOut()));
    connect(tim2,SIGNAL(timeout()),this,SLOT(OnTest()));
    tim2->start();

    ui->lineEditx->setText(QString::fromStdString(regi.checkinf(2)));
    ui->lineEdity->setText(QString::fromStdString(regi.checkinf(3)));
    ui->lineEditx->setValidator(new QRegExpValidator(QRegExp("^0?|^[1-9][0-9]+$")));
    ui->lineEdity->setValidator(new QRegExpValidator(QRegExp("^0?|^[1-9][0-9]+$")));
    this->fwin = new FloatingWindow;
    fwin->move(ui->lineEditx->text().toInt(),ui->lineEdity->text().toInt());
    if(regi.check(0)){
        fwin->show();
    }
    else{
        fwin->close();
    }
    ui->startShow->setChecked(regi.check(0));
    ui->autoStart->setChecked(regi.check(1));
    ui->mess->setChecked(regi.check(2));
    is_show_message=regi.check(2);
    bgc.setNamedColor(QString::fromStdString(regi.checkinf(0)));
    wdc.setNamedColor(QString::fromStdString(regi.checkinf(1)));


    ui->bgColor->setStyleSheet(
                QString("background-color: rgb(%1, %2, %3);")
                .arg(bgc.red())
                .arg(bgc.green())
                .arg(bgc.blue()));
    ui->wdColor->setStyleSheet(
                QString("background-color: rgb(%1, %2, %3);")
                .arg(wdc.red())
                .arg(wdc.green())
                .arg(wdc.blue()));
    fwin->bgc=(bgc);
    fwin->setWdc(wdc);


    QIcon icon = QIcon("://pics/pic.ico");
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(icon);
    trayIcon->setToolTip("Huasushis VisualKeyboard");
    trayIcon->show();

    minimizeAction = new QAction("最小化", this);
    connect(minimizeAction,SIGNAL(triggered()),this,SLOT(hide()));

    restoreAction = new QAction("还原", this);
    connect(restoreAction,SIGNAL(triggered()),this,SLOT(exShowNormal()));

    quitAction = new QAction("退出",this);
    connect(quitAction,SIGNAL(triggered()),qApp,SLOT(quit()));

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
    trayIcon->setContextMenu(trayIconMenu);
    connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                this,SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_autoStart_stateChanged(int arg1)
{
    try {
        bool improveRights=0;
        improveRights=regi.EnableDebugPrivilege();
        if(improveRights){
            regi.change(arg1);
            regi.p->SetValue("Orig","self-starting",arg1?"true":"false");
            regi.p->WriteINI("vk.ini");
        }
        else{
            throw 2;
        }
    } catch (int tmp) {
        if(tmp==1){
            QMessageBox::warning(0, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("\n系统参数错误,不能随系统启动\n"));
        }
        else{
            QMessageBox::warning(0, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("\n未知错误\n"));
        }
        ui->autoStart->setChecked(!arg1);
        regi.p->SetValue("Orig","self-starting",arg1?"false":"true");
        regi.p->WriteINI("vk.ini");
    }
}

void MainWindow::on_startShow_stateChanged(int arg1)
{
    regi.p->SetValue("Orig","start",arg1?"true":"false");
    regi.p->WriteINI("vk.ini");
    if(arg1){
        fwin->move(ui->lineEditx->text().toInt(),ui->lineEdity->text().toInt());
        fwin->show();
    }
    else{
        fwin->close();
    }

}

void MainWindow::on_donate_triggered()
{
    donate *donation = new donate();
    //donation->setWindowModality(Qt::ApplicationModal);
    donation -> show();
}

void MainWindow::on_author_triggered()
{
    author *huasushis = new author();
    //huasushis -> setWindowModality(Qt::ApplicationModal);
    huasushis -> show();
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason){
    switch(reason){
    case QSystemTrayIcon::Trigger:
        if(is_show_message)
            trayIcon->showMessage("啊~~~","我终于可以露出我的绝世容颜啦！");
        showNormal();
        break;
    case QSystemTrayIcon::MiddleClick:
        trayIcon->showMessage("状态", QString(regi.check(0)?"已启动\n":"已停止\n")+QString(regi.check(1)?"开机自启动已打开\n":"开机自启动已关闭\n")+QString(regi.check(2)?"显示通知":"不显示通知"));
        break;
    default:
        break;
    }

}


void MainWindow::closeEvent(QCloseEvent *event)
{
    regi.p->SetValue("WinSetting","posx",ui->lineEditx->text().toStdString());
    regi.p->SetValue("WinSetting","posy",ui->lineEdity->text().toStdString());
    regi.p->WriteINI("vk.ini");
    qApp->quit();
    event->ignore();
}


void MainWindow::hideEvent(QHideEvent *event)
{
    if(trayIcon->isVisible())
    {
        hide();
        if(is_show_message)
            trayIcon->showMessage("提示","已隐藏到托盘图标");
        event->ignore();
    }
}

void MainWindow::on_mess_stateChanged(int arg1)
{
    try {
        regi.p->SetValue("Orig","show_message",arg1?"true":"false");
        is_show_message=arg1;
        regi.p->WriteINI("vk.ini");
    } catch (...) {
        ui->mess->setChecked(!arg1);
        regi.p->SetValue("Orig","show_message",arg1?"false":"true");
        is_show_message=!arg1;
        regi.p->WriteINI("vk.ini");
    }

}

void MainWindow::exShowNormal(){
    if(is_show_message)
        trayIcon->showMessage("啊~~~","我终于可以露出我的绝世容颜啦！");
    showNormal();
}

void MainWindow::on_bgColor_clicked()
{
    QColorDialog tmp(bgc,this);
    tmp.tr("选择背景颜色");
    tmp.setOption(QColorDialog::ShowAlphaChannel);
    if (tmp.exec()==QColorDialog::Accepted){
        bgc=tmp.currentColor();
        ui->bgColor->setStyleSheet(
                    QString("background-color: rgb(%1, %2, %3);")
                    .arg(bgc.red())
                    .arg(bgc.green())
                    .arg(bgc.blue()));
        regi.p->SetValue("WinSetting","bgColor",bgc.name(QColor::HexArgb).toStdString());
        regi.p->WriteINI("vk.ini");
        fwin->bgc=bgc;
        if(fwin->isEnabled()){
            fwin->update();
            fwin->close();
            fwin->show();
        }
    }
}

void MainWindow::on_wdColor_clicked()
{
    QColorDialog tmp(wdc,this);
    tmp.tr("选择文字颜色");
    tmp.setOption(QColorDialog::ShowAlphaChannel);
    if (tmp.exec()==QColorDialog::Accepted){
        wdc=tmp.currentColor();
        ui->wdColor->setStyleSheet(
                    QString("background-color: rgb(%1, %2, %3);")
                    .arg(wdc.red())
                    .arg(wdc.green())
                    .arg(wdc.blue()));
        regi.p->SetValue("WinSetting","wdColor",wdc.name(QColor::HexArgb).toStdString());
        regi.p->WriteINI("vk.ini");
        fwin->setWdc(wdc);
    }
}

void MainWindow::on_lineEditx_editingFinished()
{
    regi.p->SetValue("WinSetting","posx",ui->lineEditx->text().toStdString());
    regi.p->WriteINI("vk.ini");
}


void MainWindow::on_lineEdity_editingFinished()
{
    regi.p->SetValue("WinSetting","posy",ui->lineEdity->text().toStdString());
    regi.p->WriteINI("vk.ini");
}

void MainWindow::on_defaultPos_clicked()
{
    ui->lineEditx->setText(defaultPosx);
    ui->lineEdity->setText(defaultPosy);
    regi.p->SetValue("WinSetting","posx",defaultPosx);
    regi.p->SetValue("WinSetting","posy",defaultPosy);
    regi.p->WriteINI("vk.ini");
}

void MainWindow::on_CurrentPos_doubleclicked()
{
    if (fwin->isHidden()){
        if(is_show_message)
            trayIcon->showMessage("哦不(⊙o⊙)","现在没有开启窗口哦~~");
        return;
    }
    if (is_show_message)
        trayIcon->showMessage("提示","设置成功！");
    ui->lineEditx->setText(QString::number(fwin->x()));
    ui->lineEdity->setText(QString::number(fwin->y()));
    regi.p->SetValue("WinSetting","posx",QString::number(fwin->x()).toStdString());
    regi.p->SetValue("WinSetting","posy",QString::number(fwin->y()).toStdString());
    regi.p->WriteINI("vk.ini");
}

void MainWindow::OnTimeOut(){
    if(lktmp.UpdateDownKeys().empty()){
        fwin->close();
    }
}

void MainWindow::OnTest(){
    fwin->updatekey();
    if(lktmp.UpdateDownKeys().empty()){
        if(!tim->isActive()) tim->start();
    }
    else{
        tim->stop();
        fwin->show();
    }
}
