
#include <QApplication>

#include "Mainwindow.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowTitle(u8"运维工具");
    w.initUI();
    w.init();
    w.show();
    return a.exec();
}
