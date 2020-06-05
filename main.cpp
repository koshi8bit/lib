#include "mainwindow.h"
#include <QApplication>

#define SHARED_VARIABLE_PORT 11511

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    InitNVServer sharedVariableServer(SHARED_VARIABLE_PORT);
    //InitNVClient sharedVariableClient("192.168.0.221", SHARED_VARIABLE_PORT, 5000);
    //InitNVClient sharedVariableClient("127.0.0.1", SHARED_VARIABLE_PORT, 5000);

    MainWindow w;
    w.show();

    return a.exec();
}

