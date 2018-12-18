#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    configureNewPlots();
    configureGraphs();

    timerAddData1 = new QTimer(this);
    timerAddData1->setInterval(addData1MSEC);
    connect(timerAddData1, SIGNAL(timeout()), this, SLOT(addData1()));
    timerAddData1->start();

    timerAddData2 = new QTimer(this);
    timerAddData2->setInterval(addData2MSEC);
    connect(timerAddData2, SIGNAL(timeout()), this, SLOT(addData2()));
    timerAddData2->start();

    timerReplot = new QTimer(this);
    timerReplot->setInterval(plotUpdateIntervalMSEC);
    connect(timerReplot, SIGNAL(timeout()), this, SLOT(replot()));
    timerReplot->start();
}



void MainWindow::configureNewPlots()
{
    mg = new QCPMarginGroup(ui->rtPlotHighVoltageCurrent->plot());

    ui->rtPlotHighVoltageCurrent->setAxisLabel(RTPlotWithLegend::Axis::yAxis, "Энергия (кВ)");
    ui->rtPlotHighVoltageCurrent->setAxisLabel(RTPlotWithLegend::Axis::yAxis2, "Ток (мА)");
    ui->rtPlotHighVoltageCurrent->setMarginGroup(mg);
    connect(ui->rtPlotHighVoltageCurrent->plot()->xAxis,SIGNAL(rangeChanged(QCPRange)),this,SLOT(changeRange(QCPRange)));
    connect(ui->rtPlotHighVoltageCurrent->plot(), SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));
    connect(ui->rtPlotHighVoltageCurrent, &RTPlotWithLegend::realTimeChanged, this, &MainWindow::plotRealTimeChanged);

    connect(ui->rtPlotHighVoltageCurrent->plot(), SIGNAL(afterReplot()), ui->rtPlotTemperaturePower->plot(), SLOT(replot()));
    connect(ui->rtPlotHighVoltageCurrent->plot(), SIGNAL(afterReplot()), ui->rtPlotVacuumRadiation->plot(), SLOT(replot()));



    ui->rtPlotTemperaturePower->setAxisLabel(RTPlotWithLegend::Axis::yAxis, "Температура (С)");
    ui->rtPlotTemperaturePower->setAxisLabel(RTPlotWithLegend::Axis::yAxis2, "Мощность (Вт)");
    ui->rtPlotTemperaturePower->setMarginGroup(mg);
    connect(ui->rtPlotTemperaturePower->plot()->xAxis,SIGNAL(rangeChanged(QCPRange)),this,SLOT(changeRange(QCPRange)));
    connect(ui->rtPlotTemperaturePower->plot(), SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));
    connect(ui->rtPlotTemperaturePower, &RTPlotWithLegend::realTimeChanged, this, &MainWindow::plotRealTimeChanged);



    ui->rtPlotVacuumRadiation->setAxisLabel(RTPlotWithLegend::Axis::yAxis, "Вакуум (Пa)", QCPAxis::ScaleType::stLogarithmic);
    ui->rtPlotVacuumRadiation->setAxisLabel(RTPlotWithLegend::Axis::yAxis2, "Радиация (Зв)");
    ui->rtPlotVacuumRadiation->setMarginGroup(mg);
    connect(ui->rtPlotVacuumRadiation->plot()->xAxis,SIGNAL(rangeChanged(QCPRange)),this,SLOT(changeRange(QCPRange)));
    connect(ui->rtPlotVacuumRadiation->plot(), SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));
    connect(ui->rtPlotVacuumRadiation, &RTPlotWithLegend::realTimeChanged, this, &MainWindow::plotRealTimeChanged);


}




void MainWindow::addData1()
{
    geHighVoltageElvFull->addData(now, sin(5.0f/2*cos(now)));
    geTemperaturePyrometer->addData(now, sin(9.0f/2*cos(now)));


}

void MainWindow::addData2()
{
    gehCurrentBergozHebt->addData(now, QRandomGenerator::global()->bounded(1.0));
    geHighVoltageElvFirstSection->addData(now, sin(now));
    geVacuumTandem->addData(now, qPow(qSin(now), 2) - 2*qSin(now) - 2);

}

void MainWindow::replot()
{
    now = RTPlotWithLegend::now();

    if (ui->rtPlotHighVoltageCurrent->realTime())
    {
        ui->rtPlotHighVoltageCurrent->plot()->xAxis->setRange(now - ui->rtPlotHighVoltageCurrent->timeAxisRangeSEC(), now);
    }

    ui->rtPlotHighVoltageCurrent->plot()->replot();
}



void MainWindow::configureGraphs()
{
    configureGraphsEnergyCurrent();
    configureGraphsTemperaturePower();
    configureGraphsVacuumRadiation();
}

void MainWindow::configureGraphsEnergyCurrent()
{
    geHighVoltageElvFull = ui->rtPlotHighVoltageCurrent->addGraph(RTPlotWithLegend::Axis::yAxis, "ЭЛВ (полное напряжение)");
    geHighVoltageElvFirstSection = ui->rtPlotHighVoltageCurrent->addGraph(RTPlotWithLegend::Axis::yAxis, "ЭЛВ (первая секция)");
    gehCurrentBergozHebt = ui->rtPlotHighVoltageCurrent->addGraph(RTPlotWithLegend::Axis::yAxis2, "Bergoz (выс. эн. тракт)");
}

void MainWindow::configureGraphsTemperaturePower()
{
    geTemperaturePyrometer = ui->rtPlotTemperaturePower->addGraph(RTPlotWithLegend::Axis::yAxis, "Пирометр");
}

void MainWindow::configureGraphsVacuumRadiation()
{
    geVacuumTandem = ui->rtPlotVacuumRadiation->addGraph(RTPlotWithLegend::Axis::yAxis, "Тандем");
}




MainWindow::~MainWindow()
{
    mg->deleteLater();
    delete ui;
}

void MainWindow::on_checkBoxRealTime_stateChanged(int arg1)
{
    plotUpdateRealTIme = static_cast<bool>(arg1);

    ui->rtPlotHighVoltageCurrent->setRealTime(plotUpdateRealTIme);
    ui->rtPlotTemperaturePower->setRealTime(plotUpdateRealTIme);
    ui->rtPlotVacuumRadiation->setRealTime(plotUpdateRealTIme);
}


////////////////////////////////

void MainWindow::changeRange(QCPRange range)
{
    QCPAxis* axis = static_cast<QCPAxis *>(QObject::sender());

    if (axis != ui->rtPlotHighVoltageCurrent->plot()->xAxis)
        ui->rtPlotHighVoltageCurrent->plot()->xAxis->setRange(range);
    if (axis != ui->rtPlotTemperaturePower->plot()->xAxis)
        ui->rtPlotTemperaturePower->plot()->xAxis->setRange(range);
    if (axis != ui->rtPlotVacuumRadiation->plot()->xAxis)
        ui->rtPlotVacuumRadiation->plot()->xAxis->setRange(range);

    ui->rtPlotHighVoltageCurrent->plot()->replot();
}


void MainWindow::mouseMove(QMouseEvent *event)
{
    auto plot = static_cast<QCustomPlot*>(sender());
    auto time = plot->xAxis->pixelToCoord(event->x());

    if (plot != ui->rtPlotHighVoltageCurrent->plot())
        ui->rtPlotHighVoltageCurrent->mouseMove(time);
    if (plot != ui->rtPlotTemperaturePower->plot())
        ui->rtPlotTemperaturePower->mouseMove(time);
    if (plot != ui->rtPlotVacuumRadiation->plot())
        ui->rtPlotVacuumRadiation->mouseMove(time);

    ui->rtPlotHighVoltageCurrent->plot()->replot();
}


void MainWindow::plotRealTimeChanged(bool newValue)
{
    ui->checkBoxRealTime->setChecked(newValue);
    auto plot = static_cast<RTPlotWithLegend *>(sender());

    if (plot != ui->rtPlotHighVoltageCurrent)
        ui->rtPlotHighVoltageCurrent->setRealTime(newValue);
    if (plot != ui->rtPlotTemperaturePower)
        ui->rtPlotTemperaturePower->setRealTime(newValue);
    if (plot != ui->rtPlotVacuumRadiation)
        ui->rtPlotVacuumRadiation->setRealTime(newValue);

}

