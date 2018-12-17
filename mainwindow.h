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
#include "plot/graphelement.h"
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
    int plotScreenBufferSEC = 90;
    int plotUpdateIntervalMSEC = 10;


    QTimer *timer;

    GraphElement *geHighVoltageElvFull, *geHighVoltageElvFirstSection, *gehCurrentBergozHebt, *geTemperaturePyrometer, *geVacuumTandem;


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
    void drawData();
    void changeRange(QCPRange range);
    void on_checkBoxRealTime_stateChanged(int arg1); 
    void mouseMove(QMouseEvent *event);
};

#endif // MAINWINDOW_H
