#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QTimer>
#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class QCPAxis;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



    void configureGraphEnergyCurrent();

private:
    Ui::MainWindow *ui;
    void configurePlotEnergyCurrent(QCustomPlot *plot, const QString &y1Label, const QString &y2Label);
    bool plotUpdateRealTIme;
    int plotScreenBufferSEC = 120;

    QTimer *timer;

    QCPGraph *graphEnergy, *graphCurrent, *graphTemperature;


    void configureGraph();
    void configurePlot();


private slots:
    void drawData();
    void changeRanges(QCPRange range);
    void on_checkBox_stateChanged(int arg1);
};

#endif // MAINWINDOW_H
