#-------------------------------------------------
#
# Project created by QtCreator 2020-03-09T20:11:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FloatWidget
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

win32 {
    SOURCES += \
            floatwidget_win.cpp

    HEADERS += \
            floatwidget_win.h
}

unix:!macx {
    CONFIG += link_pkgconfig
    PKGCONFIG += xext
    QT += x11extras dbus
    LIBS += -lX11

    SOURCES += xutil.cpp \
        floatwidget_linux.cpp

    HEADERS += xutil.h \
        floatwidget_linux.h
}

SOURCES += \
        main.cpp




# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
