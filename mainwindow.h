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
    void configurePlotLabel(QCustomPlot *plot, const QString &y1Label, const QString &y2Label);
    bool plotUpdateRealTIme;
    int plotScreenBufferSEC = 60*5;
    int plotUpdateIntervalMSEC = 100;

    QTimer *timer;

    QCPGraph *graphEnergy, *graphCurrent, *graphTemperature;


    void configureGraph();
    void configurePlot();
    void configurePlotBackground(QCustomPlot *plot);


    void configurePlotAxis(QCPAxis *axis);

private slots:
    void drawData();
    void changeRange(QCPRange range);
    void on_checkBox_stateChanged(int arg1);
};

#endif // MAINWINDOW_H
