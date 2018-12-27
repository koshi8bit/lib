#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QTimer>
#include <QRandomGenerator>
#include <QtMath>

#include "plot/qcustomplot.h"
#include "plot/axisconfig.h"
#include "plot/colorsetter.h"
#include "plot/graph.h"
#include "plot/graphlegenditem.h"

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
    bool plotUpdateRealTIme;
    int plotUpdateIntervalMSEC = 10;
    int addData1MSEC = 50;
    int addData2MSEC = 1000;


    QTimer *timerAddData1, *timerAddData2, *timerReplot;

    Graph *graphHighVoltageElvFull, *graphHighVoltageElvFirstSection, *graphCurrentBergozHebt;
    Graph *graphTemperaturePyrometer;
    Graph *graphVacuumTandem;

    QCPMarginGroup *mg;
    double now;
    QDateTime time;

    void configureGraphs();
    void configureGraphsEnergyCurrent();
    void configureGraphsTemperaturePower();
    void configureGraphsVacuumRadiation();

    //////////////
    void configureNewPlots();

private slots:
    void addData1();
    void addData2();
    void replot();
    void on_checkBoxRealTime_stateChanged(int arg1);

    void plotChangeRange(QCPRange range);
    void plotMouseMove(QMouseEvent *event);
    void plotRealTimeChanged(bool newValue);
    void plotMoveLineRealTimeChanged(bool newValue);
};

#endif // MAINWINDOW_H
