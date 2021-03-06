#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QTimer>
#include <QRandomGenerator>
#include <QtMath>
#include <QDateTime>


#include <lib/kb4/ui/plots/base/colorsetter.h>
#include <lib/kb4/ui/plots/base/graphlegenditem.h>
#include <lib/kb4/log/channeldouble.h>
#include <lib/kb4/log/excel/timelog/timelog.h>
#include <lib/kb4/errorhandler/errorhandler.h>
#include <lib/kb4/qdebuglogger/qdebuglogger.h>
#include <lib/kb4/worker/worker.h>
#include <lib/kb4/log/simple/simplelog.h>
#include <lib/kb4/ui/plots/radar/radartemperature4graph.h>
#include <lib/kb4/ui/faults/faultswidget.h>

#include <lib/kb4/ui/plots/simple/simpleplot.h>
#include <lib/kb4/ui/plots/simple/simplegraph.h>

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
    int plotUpdateIntervalMSEC = 10;
    int addData1MSEC = 50;
    int addData2MSEC = 1000;

    QTimer *timerAddData1, *timerAddData2, *timerrealTimeQcpReplot, *timer;

    RealTimeGraph *graphHighVoltageElvFull, *graphHighVoltageElvFirstSection, *graphCurrentBergozHebt;
    RealTimeGraph *graphTemperaturePyrometer;
    RealTimeGraph *graphVacuumTandem;

    RealTimeGraph *graphRealTimeQcpUa, *graphRealTimeQcpUb, *graphRealTimeQcpIa, *graphRealTimeQcpBoola;

    QCPMarginGroup *mgColumn0, *mgColumn1;
    //double now;
    QDateTime time;

    TimeLog *excelLog;
    ChannelDouble *a, *b, *c, *d;
    ChannelDouble *deletingTest;
    ChannelT<QDateTime> *t;

    QSettings *settings;
    QTimer *timerRealTimeQcpReplot;
    SimpleLog *simpleLog;

    RadarTemperature4Graph *radarTestGraph;

    void dateTimeDeltaTests();

    Fault *fault1, *fault2;

    FaultsWidget *faultsWidget;
    void configureFaults();



    void configureRealTimeQcpPlot();
    void configureRealTimeQcpPlot(RealTimePlot *plot);

    void configureRealTimeQcpGraphs();
    void configureRealTimeQcpPlotDayStyle();

    void configureGradientLineEdit();
    
    void configureTimers();
    
    void configureExcelLog();

    Worker *w;
    void configureWorker();
    void heavyWork();

    void configureValueDouble();

    void qLocaleTest();

    void writeFileTest();

    void simpleLogTest();

    void radarPlotTest();

    void pathConcatTest();

    void doubleValueScaleTest();

    void testingGraphErrorXY();
    
    void testingValueBuffered();
    
public slots:
    void valueDoubleCopyedToClipboard(QString newValue, QString message);

    
private slots:
    void addData1();
    void addData2();

    void realTimeQcpSetTimeAxisRange(QCPRange range);
    void realTimeQcpSetCursorKey(double key);
    void realTimeQcpSetRealTime(bool newValue);
    void realTimeQcpSetMoveLineRealTime(bool newValue);
    void realTimeQcpSetCursor2Visible(bool newValue);
    void realTimeQcpSetCursor2Key(double key);

    void plotLineRealTimeMoved();
    void on_horizontalSlider_valueChanged(int value);
    void gradientLineEdit_rangeChanged(double min, double max);
    void on_pushButtonLogCommit_clicked();
    void on_pushButtonLogPush_clicked();
    void on_checkBox_stateChanged(int arg1);
    void on_pushButton_clicked();
    void on_pushButtonExit_clicked();

    void on_pushButton_2_clicked();
    void on_pushButtonNow_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_doubleSpinBoxRadarRadius_valueChanged(double arg1);
    void on_doubleSpinBoxRadarAngle_valueChanged(double arg1);
    void on_pushButtonRadarCalc_clicked();
    void on_pushButtonAddPlot_clicked();
    void on_pushButtonDeletePlot_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_checkBoxFault1_toggled(bool checked);
    void on_checkBoxFault2_toggled(bool checked);
};

#endif // MAINWINDOW_H
