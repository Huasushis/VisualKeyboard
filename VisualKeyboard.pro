QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += -O3 -std=c++14 -s

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    author.cpp \
    cmyini.cpp \
    donate.cpp \
    floatingwindow.cpp \
    listenkeyboard.cpp \
    main.cpp \
    mainwindow.cpp \
    qtclickablelabel.cpp \
    reg.cpp

HEADERS += \
    author.h \
    cmyini.h \
    donate.h \
    floatingwindow.h \
    listenkeyboard.h \
    mainwindow.h \
    qtclickablelabel.h \
    reg.h

FORMS += \
    author.ui \
    donate.ui \
    floatingwindow.ui \
    mainwindow.ui

TRANSLATIONS += \
    VisualKeyboard_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    Images.qrc

#DISTFILES += \
#    version.rc
#RC_ICONS = pic.ico

RC_FILE += version.rc
