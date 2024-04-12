#include <QApplication>
#include "mainwindow.h"



int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    main_window mainwindow;
    mainwindow.show();
    return QApplication::exec();
}
