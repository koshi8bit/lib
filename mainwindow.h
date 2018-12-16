#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QTimer>
#include <QRandomGenerator>
#include <QtMath>

#include "qcustomplot.h"
#include "plot/axisconfig.h"
#include "plot/colorsetter.h"
#include "plot/graphelement.h"

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
    int plotScreenBufferSEC = 60*2;
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
    void axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);
    void axisClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);
    //void mouseMove(QMouseEvent *event);
    //void configureGraphs1();
};

#endif // MAINWINDOW_H
