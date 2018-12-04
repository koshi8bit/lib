#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>
#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    void configurePlotEnergyCurrent(QCustomPlot *plot, const QString &y1Label, const QString &y2Label);

private slots:
    void changeRanges(QCPRange range);
};

#endif // MAINWINDOW_H
