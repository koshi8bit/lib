#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QTimer>
#include <QRandomGenerator>
#include <QtMath>

#include "qcustomplot.h"
#include "axisconfig.h"
#include "colorsetter.h"

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
    void configurePlot(QCustomPlot *plot, const QString &y1Label, const QString &y2Label, QCPMarginGroup *mg, QCPItemLine **line);
    bool plotUpdateRealTIme;
    int plotScreenBufferSEC = 60*2;
    int plotUpdateIntervalMSEC = 10;


    QTimer *timer;

    QCPGraph *graphHighVoltageElvFull, *graphHighVoltageElvFirstSection, *graphCurrentBergozHebt, *graphTemperaturePyrometer, *graphVacuumTandem;
    QCPItemTracer *tracerHighVoltageElvFull, *tracerHighVoltageElvFirstSection, *tracerCurrentBergozHebt, *tracerTemperaturePyrometer, *tracerVacuumTandem;

    QCPItemLine *lineHighVoltageCurrent, *lineTemperaturePower, *lineVacuumRadiation;

    void configureGraphs();

    void configurePlots();
    void configurePlotBackground(QCustomPlot *plot);
    void configurePlotZoomAndDrag(QCustomPlot *plot, bool zoomAndDragTimeAxis);
    void configurePlotBackgroundAxis(QCPAxis *axis);

    QCPMarginGroup *mg;
    double now;
    QDateTime time;

    void configurePlotHighVoltageCurrent();
    void configurePlotTemperaturePower();
    void configurePlotVacuumRadiation();


    void configureGraphsEnergyCurrent();
    void configureGraphsTemperaturePower();
    void configureGraphsVacuumRadiation();


private slots:
    void drawData();
    void changeRange(QCPRange range);
    void on_checkBoxRealTime_stateChanged(int arg1);
    void axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);
    void axisClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);
    void mouseMove(QMouseEvent *event);
    //void configureGraphs1();
};

#endif // MAINWINDOW_H
