#ifndef PRINTSCREENER_H
#define PRINTSCREENER_H

#include <QApplication>
#include <QObject>
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>

#include <lib/kb4/easyliving.h>



class PrintScreener
{
public:
    PrintScreener();
    static bool save(QWidget *widget);
};

#endif // PRINTSCREENER_H
