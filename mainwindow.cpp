#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    configureNewPlots();
    configureGraphs();

    timer = new QTimer(this);
    timer->setInterval(plotUpdateIntervalMSEC);
    connect(timer, SIGNAL(timeout()), this, SLOT(drawData()));
    timer->start();
}



void MainWindow::configureNewPlots()
{
    mg = new QCPMarginGroup(ui->rtPlotHighVoltageCurrent->plot());

    ui->rtPlotHighVoltageCurrent->setAxisLabel(RTPlotWithLegend::Axis::yAxis, "Энергия (кВ)");
    ui->rtPlotHighVoltageCurrent->setAxisLabel(RTPlotWithLegend::Axis::yAxis2, "Ток (мА)");
    ui->rtPlotHighVoltageCurrent->setMarginGroup(mg);
    connect(ui->rtPlotHighVoltageCurrent->plot()->xAxis,SIGNAL(rangeChanged(QCPRange)),this,SLOT(changeRange(QCPRange)));
    connect(ui->rtPlotHighVoltageCurrent->plot(), SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));
    connect(ui->rtPlotHighVoltageCurrent->plot(), SIGNAL(afterReplot()), ui->rtPlotTemperaturePower->plot(), SLOT(replot()));
    connect(ui->rtPlotHighVoltageCurrent->plot(), SIGNAL(afterReplot()), ui->rtPlotVacuumRadiation->plot(), SLOT(replot()));

    ui->rtPlotTemperaturePower->setAxisLabel(RTPlotWithLegend::Axis::yAxis, "Температура (С)");
    ui->rtPlotTemperaturePower->setAxisLabel(RTPlotWithLegend::Axis::yAxis2, "Мощность (Вт)");
    ui->rtPlotTemperaturePower->setMarginGroup(mg);
    connect(ui->rtPlotTemperaturePower->plot()->xAxis,SIGNAL(rangeChanged(QCPRange)),this,SLOT(changeRange(QCPRange)));
    connect(ui->rtPlotTemperaturePower->plot(), SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));

    ui->rtPlotVacuumRadiation->setAxisLabel(RTPlotWithLegend::Axis::yAxis, "Вакуум (Пa)", QCPAxis::ScaleType::stLogarithmic);
    ui->rtPlotVacuumRadiation->setAxisLabel(RTPlotWithLegend::Axis::yAxis2, "Радиация (Зв)");
    ui->rtPlotVacuumRadiation->setMarginGroup(mg);
    connect(ui->rtPlotVacuumRadiation->plot()->xAxis,SIGNAL(rangeChanged(QCPRange)),this,SLOT(changeRange(QCPRange)));
    connect(ui->rtPlotVacuumRadiation->plot(), SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));

}




void MainWindow::drawData()
{
    time = QDateTime::currentDateTime();
    now = time.toTime_t() + static_cast<double>(time.time().msec())/1000;

    geHighVoltageElvFull->addData(now, sin(5.0f/2*cos(now)));
    geHighVoltageElvFirstSection->addData(now, sin(now));
    gehCurrentBergozHebt->addData(now, QRandomGenerator::global()->bounded(1.0));
    geTemperaturePyrometer->addData(now, sin(9.0f/2*cos(now)));
    geVacuumTandem->addData(now, qPow(qSin(now), 2) - 2*qSin(now) - 2);


    if (ui->checkBoxRealTime->isChecked())
    {
        ui->rtPlotHighVoltageCurrent->plot()->xAxis->setRange(now - plotScreenBufferSEC, now);
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


void MainWindow::changeRange(QCPRange range)
{
    QCPAxis* axis = static_cast<QCPAxis *>(QObject::sender());

    if (axis != ui->rtPlotHighVoltageCurrent->plot()->xAxis)
        ui->rtPlotHighVoltageCurrent->plot()->xAxis->setRange(range);
    if (axis != ui->rtPlotTemperaturePower->plot()->xAxis)
        ui->rtPlotTemperaturePower->plot()->xAxis->setRange(range);
    if (axis != ui->rtPlotVacuumRadiation->plot()->xAxis)
        ui->rtPlotVacuumRadiation->plot()->xAxis->setRange(range);

    plotScreenBufferSEC = range.upper - range.lower;

    ui->rtPlotHighVoltageCurrent->plot()->replot();
}


void MainWindow::on_checkBoxRealTime_stateChanged(int arg1)
{
    plotUpdateRealTIme = static_cast<bool>(arg1);

    ui->rtPlotHighVoltageCurrent->configurePlotZoomAndDrag(!plotUpdateRealTIme);
    ui->rtPlotTemperaturePower->configurePlotZoomAndDrag(!plotUpdateRealTIme);
    ui->rtPlotVacuumRadiation->configurePlotZoomAndDrag(!plotUpdateRealTIme);
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
