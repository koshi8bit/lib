#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QTimer>
#include <QRandomGenerator>
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



    void configureGraphEnergyCurrent();



private:
    Ui::MainWindow *ui;
    void configurePlot(QCustomPlot *plot, const QString &y1Label, const QString &y2Label, QCPMarginGroup *mg);
    bool plotUpdateRealTIme;
    int plotScreenBufferSEC = 60*5;
    int plotUpdateIntervalMSEC = 100;

    QTimer *timer;

    QCPGraph *graphEnergy, *graphCurrent, *graphTemperature;


    void configureGraphs();
    void configurePlots();
    void configurePlotBackground(QCustomPlot *plot);


    void configurePlotBackgroundAxis(QCPAxis *axis);

    QCPMarginGroup *mg;
    double rangeDelta = 200;
    double now;

private slots:
    void drawData();
    void changeRange(QCPRange range);
    void on_checkBoxRealTime_stateChanged(int arg1);
    void on_editRange_editingFinished();
};

#endif // MAINWINDOW_H
