#include "mainwindow.h"
#include <QApplication>

#define SHARED_VARIABLE_PORT 11511

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    InitNVServer sharedVariableServer(SHARED_VARIABLE_PORT);

    MainWindow w;
    w.show();

    return a.exec();
}
