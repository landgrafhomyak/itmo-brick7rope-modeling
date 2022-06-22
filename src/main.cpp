#include <cstdio>

#include <QApplication>
#include "mainwindow.hpp"


int main(int argc, char *argv[])
{
    printf("hello_world");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QApplication::exec();
}
