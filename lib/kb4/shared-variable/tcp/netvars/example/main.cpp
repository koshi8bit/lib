#include "mainwindow.h"
#include <QApplication>
#include "netvars.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //InitNVServer s(27015);
    InitNVClient c("127.0.0.1",27015,5000);

    MainWindow w;
    w.show();

    return a.exec();
}
