#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QTimer>
#include <QRandomGenerator>
#include <QtMath>

#include <lib/kb4/ui/rtplotwithlegend/axisconfig.h>
#include <lib/kb4/ui/rtplotwithlegend/colorsetter.h>
#include <lib/kb4/ui/rtplotwithlegend/graph.h>
#include <lib/kb4/ui/rtplotwithlegend/graphlegenditem.h>
#include <lib/kb4/ui/rtplotwithlegend/axis2/rtplotwithlegend.h>
#include <lib/kb4/log/channeldouble.h>
#include <lib/kb4/log/excel/timelog/timelog.h>
#include <lib/qcustomplot/qcustomplot.h>
#include <lib/kb4/errorhandler/errorhandler.h>
#include <lib/kb4/qdebuglogger/qdebuglogger.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



    ErrorHandler eh;


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

    TimeLog *excelLog;
    ChannelDouble *a, *b, *c;

    QSettings *settings;

    void configurePlots();
    void configurePlot(RTPlotWithLegend *rtPlot, QString yAxisLabel, double yAxisMin, double yAxisMax, QCPAxis::ScaleType yAxisScaleType, QString yAxis2Label, double yAxis2Min, double yAxis2Max, QCPAxis::ScaleType yAxis2ScaleType);

    void configureGraphs();
    void configureGraphsEnergyCurrent();
    void configureGraphsTemperaturePower();
    void configureGraphsVacuumRadiation();

    void configureGradientLineEdit();
    
    void configureTimers();
    
    void configureExcelLog();
    
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
    void on_horizontalSlider_valueChanged(int value);
    void gradientLineEdit_rangeChanged(double min, double max);
    void on_pushButtonLogCommit_clicked();
    void on_pushButtonLogPush_clicked();
    void on_checkBox_stateChanged(int arg1);
    void on_pushButton_clicked();
    void on_pushButtonExit_clicked();

};

#endif // MAINWINDOW_H
