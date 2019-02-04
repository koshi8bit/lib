#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QTimer>
#include <QRandomGenerator>
#include <QtMath>

#include <lib/qcustomplot/qcustomplot.h>

#include "lib/kb4/ui/axisconfig.h"
#include "lib/kb4/ui/colorsetter.h"
#include "lib/kb4/ui/graph.h"
#include "lib/kb4/ui/graphlegenditem.h"
#include "lib/kb4/ui/rtplotwithlegend.h"

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

    void configurePlots();
    void configurePlot(RTPlotWithLegend *rtPlot, QString yAxisLabel, double yAxisMin, double yAxisMax, QCPAxis::ScaleType yAxisScaleType, QString yAxis2Label, double yAxis2Min, double yAxis2Max, QCPAxis::ScaleType yAxis2ScaleType);

    void configureGraphs();
    void configureGraphsEnergyCurrent();
    void configureGraphsTemperaturePower();
    void configureGraphsVacuumRadiation();

private slots:
    void addData1();
    void addData2();
    void on_checkBoxRealTime_stateChanged(int arg1);

    void plotChangeRange(QCPRange range);
    void plotMouseMove(QMouseEvent *event);
    void plotRealTimeChanged(bool newValue);
    void plotMoveLineRealTimeChanged(bool newValue);
    void plotReplotTimeout();
    void plotLineRealTimeMoved();
};

#endif // MAINWINDOW_H
