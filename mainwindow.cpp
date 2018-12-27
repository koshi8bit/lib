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

    ui->rtPlotHighVoltageCurrent->configureAxis(RTPlotWithLegend::Axis::yAxis, "Энергия (кВ)", 0, 1250);
    ui->rtPlotHighVoltageCurrent->configureAxis(RTPlotWithLegend::Axis::yAxis2, "Ток (мА)", 0, 10);
    ui->rtPlotHighVoltageCurrent->setMarginGroup(mg);
    connect(ui->rtPlotHighVoltageCurrent->plot()->xAxis,SIGNAL(rangeChanged(QCPRange)),this,SLOT(plotChangeRange(QCPRange)));
    connect(ui->rtPlotHighVoltageCurrent->plot(), SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(plotMouseMove(QMouseEvent*)));
    connect(ui->rtPlotHighVoltageCurrent, &RTPlotWithLegend::realTimeChanged, this, &MainWindow::plotRealTimeChanged);
    connect(ui->rtPlotHighVoltageCurrent, &RTPlotWithLegend::moveLineRealTimeChanged, this, &MainWindow::plotMoveLineRealTimeChanged);

    connect(ui->rtPlotHighVoltageCurrent->plot(), SIGNAL(afterReplot()), ui->rtPlotTemperaturePower->plot(), SLOT(replot()));
    connect(ui->rtPlotHighVoltageCurrent->plot(), SIGNAL(afterReplot()), ui->rtPlotVacuumRadiation->plot(), SLOT(replot()));



    ui->rtPlotTemperaturePower->configureAxis(RTPlotWithLegend::Axis::yAxis, "Температура (С)", 0, 100);
    ui->rtPlotTemperaturePower->configureAxis(RTPlotWithLegend::Axis::yAxis2, "Мощность (Вт)", 0, 700);
    ui->rtPlotTemperaturePower->setMarginGroup(mg);
    connect(ui->rtPlotTemperaturePower->plot()->xAxis,SIGNAL(rangeChanged(QCPRange)),this,SLOT(plotChangeRange(QCPRange)));
    connect(ui->rtPlotTemperaturePower->plot(), SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(plotMouseMove(QMouseEvent*)));
    connect(ui->rtPlotTemperaturePower, &RTPlotWithLegend::realTimeChanged, this, &MainWindow::plotRealTimeChanged);



    ui->rtPlotVacuumRadiation->configureAxis(RTPlotWithLegend::Axis::yAxis, "Вакуум (Пa)", 0.00001, 1, QCPAxis::ScaleType::stLogarithmic);
    ui->rtPlotVacuumRadiation->configureAxis(RTPlotWithLegend::Axis::yAxis2, "Радиация (Зв)", 0.000001, 1, QCPAxis::ScaleType::stLogarithmic);
    ui->rtPlotVacuumRadiation->setMarginGroup(mg);
    connect(ui->rtPlotVacuumRadiation->plot()->xAxis,SIGNAL(rangeChanged(QCPRange)),this,SLOT(plotChangeRange(QCPRange)));
    connect(ui->rtPlotVacuumRadiation->plot(), SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(plotMouseMove(QMouseEvent*)));
    connect(ui->rtPlotVacuumRadiation, &RTPlotWithLegend::realTimeChanged, this, &MainWindow::plotRealTimeChanged);

}




void MainWindow::addData1()
{
    graphHighVoltageElvFull->addData(now, sin(5.0f/2*cos(now)));
    graphTemperaturePyrometer->addData(now, sin(9.0f/2*cos(now)));


}

void MainWindow::addData2()
{
    graphCurrentBergozHebt->addData(now, QRandomGenerator::global()->bounded(1.0));
    graphHighVoltageElvFirstSection->addData(now, sin(now));
    graphVacuumTandem->addData(now, qPow(qSin(now), 2) - 2*qSin(now) - 2);

}

//FIXME tima45 diff?
//void MainWindow::replot()
//{
//    auto now = RTPlotWithLegend::now();
//    auto rtPlot = ui->rtPlotHighVoltageCurrent;

//    if (rtPlot->realTime())
//    {
//        rtPlot->plot()->xAxis->setRange(
//                    now - rtPlot->timeAxisRangeSEC(),
//                    now);
//    }

//    rtPlot->plot()->replot();
//}

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
    graphHighVoltageElvFull = ui->rtPlotHighVoltageCurrent->addGraph(RTPlotWithLegend::Axis::yAxis, "ЭЛВ (полное напряжение)");
    graphHighVoltageElvFirstSection = ui->rtPlotHighVoltageCurrent->addGraph(RTPlotWithLegend::Axis::yAxis, "ЭЛВ (первая секция)");
    graphCurrentBergozHebt = ui->rtPlotHighVoltageCurrent->addGraph(RTPlotWithLegend::Axis::yAxis2, "Bergoz (выс. эн. тракт)");
}

void MainWindow::configureGraphsTemperaturePower()
{
    graphTemperaturePyrometer = ui->rtPlotTemperaturePower->addGraph(RTPlotWithLegend::Axis::yAxis, "Пирометр");
}

void MainWindow::configureGraphsVacuumRadiation()
{
    graphVacuumTandem = ui->rtPlotVacuumRadiation->addGraph(RTPlotWithLegend::Axis::yAxis, "Тандем");
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

void MainWindow::plotChangeRange(QCPRange range)
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

void MainWindow::plotMouseMove(QMouseEvent *event)
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

void MainWindow::plotMoveLineRealTimeChanged(bool newValue)
{
    auto plot = static_cast<RTPlotWithLegend *>(sender());

    if (plot != ui->rtPlotHighVoltageCurrent)
        ui->rtPlotHighVoltageCurrent->setMoveLineRealTime(newValue);
    if (plot != ui->rtPlotTemperaturePower)
        ui->rtPlotTemperaturePower->setMoveLineRealTime(newValue);
    if (plot != ui->rtPlotVacuumRadiation)
        ui->rtPlotVacuumRadiation->setMoveLineRealTime(newValue);
}
