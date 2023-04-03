
#include <QApplication>

#include "ui/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowTitle(u8"运维工具");
    w.initUI();
    w.show();
    return a.exec();
}