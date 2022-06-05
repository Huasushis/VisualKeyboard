#include "floatingwindow.h"
#include "ui_floatingwindow.h"
#include <QPropertyAnimation>
#include <QShowEvent>
#include <QCloseEvent>

FloatingWindow::FloatingWindow(QWidget *parent) :
      QWidget(parent),
      ui(new Ui::FloatingWindow)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground,true);
    this->show();
    SetWindowPos((HWND)this->winId(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
    ui->nowb->setText("");
    ui->preb->setText("");
    animation=NULL;
    keys.clear();
    vkinit();
    prestiky=pretext=0;
    LastUpdateTime=0;
    tim = new QTimer();
    tim->setInterval(1);
    connect(tim,SIGNAL(timeout()),this, SLOT(Ontimeover()));
    tim->start();
}

void FloatingWindow::Ontimeover(){
    SetWindowPos((HWND)this->winId(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
}

FloatingWindow::~FloatingWindow()
{
    delete ui;
}

void FloatingWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        pos=event->globalPos();
    }
}

void FloatingWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (!event->buttons().testFlag(Qt::LeftButton)){
        return;
    }
    int dx=event->globalX()-pos.x();
    int dy=event->globalY()-pos.y();
    pos=event->globalPos();
    move(x()+dx,y()+dy);
}

void FloatingWindow::closeEvent(QCloseEvent *event){
    if(!animation){
        animation= new QPropertyAnimation(this, "windowOpacity");
        animation->setDuration(AnimationTime);
        animation->setStartValue(1);
        animation->setEndValue(0);
        connect(animation,SIGNAL(finished()), this, SLOT(close()));
        animation->start();
        event->ignore();
    }
    else{
        animation=NULL;
    }
}

void FloatingWindow::showEvent(QShowEvent *event){
    animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(AnimationTime);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    connect(animation,SIGNAL(finished()),this,SLOT(caslot()));
}

void FloatingWindow::paintEvent(QPaintEvent *event){
//    QBitmap bmp(this->size());
//    bmp.fill();
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);  //设置反锯齿渲染
    painter.setPen(Qt::NoPen);
    painter.setBrush(bgc);
    painter.drawRoundedRect(this->rect(), 20, 20);             //8 8表示圆角的x radius跟 y radius
    painter.setRenderHint(QPainter::Antialiasing, false);  //设置反锯齿渲染
//    setMask(bmp);
}

void FloatingWindow::setWdc(QColor wdc){
    ui->nowb->setStyleSheet(
        QString("background-color: rgb(0,0,0,0);\
                color: rgb(%1, %2, %3, %4);")
            .arg(wdc.red())
            .arg(wdc.green())
            .arg(wdc.blue())
            .arg(wdc.alpha()));
    ui->preb->setStyleSheet(
        QString("background-color: rgb(0,0,0,0);\
                color: rgb(%1, %2, %3, %4);")
            .arg(wdc.red())
            .arg(wdc.green())
            .arg(wdc.blue())
            .arg(int(wdc.alpha()*0.75)));
}

void FloatingWindow::caslot(){
    auto clearAnimation=[this]{return animation=NULL;};
    clearAnimation();
}

void FloatingWindow::update(){
    animation=new QPropertyAnimation();
}

void FloatingWindow::vkinit(){
    for(int i=0;i<26;i++){
        vkvalue[i+'A']=string().append(1,i+'A');
        vkvalue[i+'A'+200]=string().append(1,i+'a');
    }
    for(int i=0;i<10;i++){
        vkvalue[i+'0']=vkvalue[i+'0'+48]=string().append(1,i+'0');
    }
    vkvalue[20]="Caps";
    vkvalue[144]="NumLock";
    vkvalue[91]="Win";
    vkvalue[17]="Ctrl";
    vkvalue[18]="Alt";
    vkvalue[16]="Shift";
    vkvalue[9]="Tab";
    vkvalue[27]="Esc";
    vkvalue[46]="Del";
    vkvalue[45]="Ins";
    vkvalue[36]="Home";
    vkvalue[35]="End";
    vkvalue[33]="PaU";
    vkvalue[34]="PaD";
    vkvalue[112]="F1";
    vkvalue[113]="F2";
    vkvalue[114]="F3";
    vkvalue[115]="F4";
    vkvalue[116]="F5";
    vkvalue[117]="F6";
    vkvalue[118]="F7";
    vkvalue[119]="F8";
    vkvalue[120]="F9";
    vkvalue[121]="F10";
    vkvalue[122]="F11";
    vkvalue[123]="F12";
    vkvalue[37]="Left";
    vkvalue[38]="Up";
    vkvalue[39]="Right";
    vkvalue[40]="Down";
    vkvalue[192]="`";
    vkvalue[189]="-";
    vkvalue[187]="=";
    vkvalue[220]="\\";
    vkvalue[219]="[";
    vkvalue[221]="]";
    vkvalue[186]=";";
    vkvalue[222]="'";
    vkvalue[188]=",";
    vkvalue[190]=".";
    vkvalue[191]="/";

    vkvalue[492]="~";
    vkvalue[489]="_";
    vkvalue[487]="+";
    vkvalue[520]="|";
    vkvalue[519]="{";
    vkvalue[521]="}";
    vkvalue[486]=":";
    vkvalue[522]="\"";
    vkvalue[488]="<";
    vkvalue[490]=">";
    vkvalue[491]="?";

    vkvalue[348]=")";
    vkvalue[349]="!";
    vkvalue[350]="@";
    vkvalue[351]="#";
    vkvalue[352]="$";
    vkvalue[353]="%";
    vkvalue[354]="^";
    vkvalue[355]="&";
    vkvalue[356]="*";
    vkvalue[357]="(";

    vkvalue[111]="\\";
    vkvalue[106]="*";
    vkvalue[109]="-";
    vkvalue[107]="+";
    vkvalue[110]=".";
    vkvalue[8]="<-";
    vkvalue[1]="左键";
    vkvalue[2]="右键";
    vkvalue[4]="中键";
    vkvalue[13]="Enter";
    vkvalue[32]="Space";

}

bool FloatingWindow::insc(int v){
    return std::find(lk.SimpleControlKeys,
                     lk.SimpleControlKeys+33,
                     v)!=lk.SimpleControlKeys+33;
}

bool FloatingWindow::inst(int v){
    return std::find(lk.SimpleTextKeys,
                     lk.SimpleTextKeys+19,
                     v)!=lk.SimpleTextKeys+19;
}

void FloatingWindow::updatekey(){
    bool stiky=false,onshift=false,alup=false;
    keys=lk.UpdateDownKeys();
    if(prestiky||!pretext){
        pres=nows;
        nows.clear();
        alup=true;
    }
    if(keys.empty()) return;
    LastUpdateTime=clock();
    prestiky=false;
    pretext=true;
    for(auto i:keys){
        if(!stiky&&insc(i)&&i!=16){
            pres=nows;
            nows.clear();
            nows.append(vkvalue[i]),
            stiky=true,
            prestiky=true;
            continue;
            pretext=false;
        }
        if(stiky) nows.append("+");
        if(i==16){
            onshift=true;
            if(stiky){
                nows.append(vkvalue[16]);
            }
         }
        else if((i>=48&&i<=57)||(i>=186&&i<=192)||(i>=219&&i<=222)){
             nows.append(vkvalue[i+onshift*300]);
        }
        else if(i!=13&&i!=32&&i!=8){
            nows.append(vkvalue[i]);
        }
        else if(i==13||i==32){
            if(!stiky&&!nows.empty()){
                pres=nows;
                nows.clear();
            }
            else{
                nows.append(vkvalue[i]);
                pretext=false;
            }
        }
        else if(i==8){
            if(!stiky&&!nows.empty()&&pretext){
                nows.pop_back();
            }
            else{
                nows.append(vkvalue[8]);
                pretext=false;
            }
        }
        else if(i!=16){
            nows.append(vkvalue[i]);
        }
        //ui->nowb->setText(QString::fromStdString(nows));
        //ui->preb->setText(QString::fromStdString(pres));
    }
    if(ui->nowb->text()!=QString::fromStdString(nows)){
        ui->nowb->setText(QString::fromStdString(nows));
        ui->preb->setText(QString::fromStdString(pres));
        QFont font;
        font.setFamily("SimSun");
        font.setPointSize(18);
        QFontMetrics fm(font);
        QRect rec=fm.boundingRect(ui->nowb->text());
        this->resize(max(rec.width()+40,101),101);
    }

}

void FloatingWindow::updatethread(){
    while(1){
        updatekey();
    }
}
