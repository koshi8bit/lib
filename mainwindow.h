#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QTimer>
#include <QRandomGenerator>
#include <QtMath>


#include <lib/kb4/ui/realtimeqcp/axisconfig.h>
#include <lib/kb4/ui/realtimeqcp/colorsetter.h>
#include <lib/kb4/ui/realtimeqcp/graph.h>
#include <lib/kb4/ui/realtimeqcp/graphlegenditem.h>
#include <lib/kb4/ui/realtimeqcp/realtimeqcp.h>
#include <lib/kb4/log/channeldouble.h>
#include <lib/kb4/log/excel/timelog/timelog.h>
#include <lib/qcustomplot/qcustomplot.h>
#include <lib/kb4/errorhandler/errorhandler.h>
#include <lib/kb4/qdebuglogger/qdebuglogger.h>
#include <lib/kb4/worker/worker.h>

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


    QTimer *timerAddData1, *timerAddData2, *timerReplot, *timerRealTimeQCPReplot;

    Graph *graphHighVoltageElvFull, *graphHighVoltageElvFirstSection, *graphCurrentBergozHebt;
    Graph *graphTemperaturePyrometer;
    Graph *graphVacuumTandem;

    Graph *graphRealTimeQcpUa, *graphRealTimeQcpUb, *graphRealTimeQcpIa, *graphRealTimeQcpBoola;

    QCPMarginGroup *mg;
    //double now;
    QDateTime time;

    TimeLog *excelLog;
    ChannelDouble *a, *b, *c;

    QSettings *settings;


    void configureRealTimeQcpPlot();
    void configureRealTimeQcpPlot(RealTimeQCP * plot);

    void configureRealTimeQcpGraphs();

    void configureGraphs();
    void configureGraphsEnergyCurrent();
    void configureGraphsTemperaturePower();
    void configureGraphsVacuumRadiation();

    void configureGradientLineEdit();
    
    void configureTimers();
    
    void configureExcelLog();

    Worker *w;
    void configureWorker();
    void heavyWork();
    
private slots:
    void addData1();
    void addData2();
    void on_checkBoxRealTime_stateChanged(int arg1);

    void realTimeQCPChangeRangeCheckPlotAxis(QCPAxis* axis, RTPlotWithLegend *plot, QCPRange range);
    void plotChangeRange(QCPRange range);
    void plotMouseMove(QMouseEvent *event);
    void plotRealTimeChanged(bool newValue);
    void plotMoveLineRealTimeChanged(bool newValue);

    void realTimeQCPChangeRangeCheckPlotAxis(RealTimeQCP *widget, QCPAxis* axis, QCPRange range);
    void realTimeQCPChangeRange(QCPRange range);
    void realTimeQCPMouseMoveCheckPlot(RealTimeQCP *widget, QCustomPlot* plot, double time);
    void realTimeQCPMouseMove(QMouseEvent *event);
    void realTimeQCPRealTimeChangedCheckWidget(RealTimeQCP *widget, RealTimeQCP *sender, bool newValue);
    void realTimeQCPRealTimeChanged(bool newValue);
    void realTimeQCPMoveLineRealTimeChangedCheckWidget(RealTimeQCP *widget, RealTimeQCP *sender, bool newValue);
    void realTimeQCPMoveLineRealTimeChanged(bool newValue);
    void timerRealTimeQCPReplotTimeout();

    void plotReplotTimeout();
    void plotLineRealTimeMoved();
    void on_horizontalSlider_valueChanged(int value);
    void gradientLineEdit_rangeChanged(double min, double max);
    void on_pushButtonLogCommit_clicked();
    void on_pushButtonLogPush_clicked();
    void on_checkBox_stateChanged(int arg1);
    void on_pushButton_clicked();
    void on_pushButtonExit_clicked();

    void on_pushButton_2_clicked();
};

#endif // MAINWINDOW_H
