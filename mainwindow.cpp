#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    configurePlots();
    configureGraphs();

    timer = new QTimer(this);
    timer->setInterval(plotUpdateIntervalMSEC);
    connect(timer, SIGNAL(timeout()), this, SLOT(drawData()));
    timer->start();
}


void MainWindow::configurePlots()
{
    ui->editRange->setEnabled(false);
    mg = new QCPMarginGroup(ui->plotEnergyCurrent);

    configurePlot(ui->plotEnergyCurrent, "Энергия (кВ)", "Ток (мА)", mg);
    connect(ui->plotEnergyCurrent,SIGNAL(afterReplot()),ui->plotTemperaturePower,SLOT(replot()));
    connect(ui->plotEnergyCurrent,SIGNAL(afterReplot()),ui->plotVacuumRadiation,SLOT(replot()));

    configurePlot(ui->plotTemperaturePower, "Температура (С)", "Мощность (Вт)", mg);

    configurePlot(ui->plotVacuumRadiation, "Вакуум (Пa)", "Радиация (Зв)", mg);
    ui->plotVacuumRadiation->yAxis->setScaleType(QCPAxis::stLogarithmic);
    QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
    ui->plotVacuumRadiation->yAxis->setTicker(logTicker);
    ui->plotVacuumRadiation->yAxis->setNumberFormat("eb");
    ui->plotVacuumRadiation->yAxis->setNumberPrecision(0);
}



void MainWindow::configurePlot(QCustomPlot *plot, const QString &y1Label, const QString &y2Label, QCPMarginGroup *mg)
{
    configurePlotZoomAndDrag(plot);
    configurePlotBackground(plot);

    plot->xAxis->setLabel("Время");
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("hh:mm:ss.z");
    plot->xAxis->setTicker(dateTicker);

    plot->yAxis->setLabel(y1Label);
    plot->yAxis->setLabelPadding(20);

    plot->yAxis2->setVisible(true);
    plot->yAxis2->setLabelPadding(30);
    plot->yAxis2->setLabel(y2Label);

    plot->axisRect()->setMarginGroup(QCP::msLeft | QCP::msRight, mg);

    //plot->setNoAntialiasingOnDrag(true);



    connect(plot->xAxis,SIGNAL(rangeChanged(QCPRange)),this,SLOT(changeRange(QCPRange)));
}


void MainWindow::configurePlotZoomAndDrag(QCustomPlot *plot)
{
    auto axes = QList<QCPAxis*>()
            << plot->xAxis
            << plot->yAxis
            << plot->yAxis2;

    plot->axisRect()->setRangeZoomAxes(axes);
    plot->axisRect()->setRangeDragAxes(axes);
}

void MainWindow::configurePlotBackground(QCustomPlot *plot)
{
    configurePlotBackgroundAxis(plot->xAxis);
    configurePlotBackgroundAxis(plot->yAxis);
    configurePlotBackgroundAxis(plot->yAxis2);


    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    plot->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(60, 60, 60));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    plot->axisRect()->setBackground(axisRectGradient);
}

void MainWindow::configurePlotBackgroundAxis(QCPAxis *axis)
{
    axis->setLabelColor(Qt::white);
    axis->setBasePen(QPen(Qt::white, 1));
    axis->setSubTickPen(QPen(Qt::white, 1));
    axis->setTickLabelColor(Qt::white);
    axis->setTickPen(QPen(Qt::white, 1));
    axis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    axis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    axis->grid()->setSubGridVisible(true);
    axis->grid()->setZeroLinePen(Qt::NoPen);
}



void MainWindow::drawData()
{
    time = QDateTime::currentDateTime();
    now = time.toTime_t() + static_cast<double>(time.time().msec())/1000;

    graphEnergy->addData(now, sin(now));
    graphTemperature->addData(now, QRandomGenerator::global()->bounded(1.0));
    graphCurrent->addData(now, cos(now)*1000);

    if (ui->checkBoxRescale->isChecked())
    {
        graphEnergy->rescaleValueAxis();
        graphTemperature->rescaleValueAxis();
        graphCurrent->rescaleValueAxis();

    }




    if (ui->checkBoxRealTime->isChecked())
    {
        ui->plotEnergyCurrent->xAxis->setRange(now - rangeDelta, now);
    }

    ui->plotEnergyCurrent->replot();
}



void MainWindow::configureGraphs()
{
    configureGraphEnergyCurrent();

    configureGraphTemperaturePower();
}

void MainWindow::configureGraphEnergyCurrent()
{
    graphEnergy = ui->plotEnergyCurrent->addGraph();
    graphEnergy->setPen(QColor(255, 255, 255));

    graphCurrent = ui->plotEnergyCurrent->addGraph();
    graphCurrent->setPen(QColor(255, 66, 66));
}

void MainWindow::configureGraphTemperaturePower()
{
    graphTemperature = ui->plotTemperaturePower->addGraph();
    graphTemperature->setPen(QColor(255, 255, 255));
}


MainWindow::~MainWindow()
{
    mg->deleteLater();
    delete ui;
}

void MainWindow::changeRange(QCPRange range)
{
    QCPAxis* axis = static_cast<QCPAxis *>(QObject::sender());

    if(axis != ui->plotEnergyCurrent->xAxis)
        ui->plotEnergyCurrent->xAxis->setRange(range);
    if(axis != ui->plotTemperaturePower->xAxis)
        ui->plotTemperaturePower->xAxis->setRange(range);
    if(axis != ui->plotVacuumRadiation->xAxis)
        ui->plotVacuumRadiation->xAxis->setRange(range);

    rangeDelta = range.upper - range.lower;
    ui->editRange->setValue(rangeDelta);

    ui->plotEnergyCurrent->replot();
}



void MainWindow::on_checkBoxRealTime_stateChanged(int arg1)
{
    plotUpdateRealTIme = static_cast<bool>(arg1);

    ui->editRange->setEnabled(!plotUpdateRealTIme);

    ui->plotEnergyCurrent->setInteraction(QCP::iRangeDrag, !plotUpdateRealTIme);
    ui->plotEnergyCurrent->setInteraction(QCP::iRangeZoom, !plotUpdateRealTIme);




    ui->plotTemperaturePower->setInteraction(QCP::iRangeDrag, !plotUpdateRealTIme);
    ui->plotTemperaturePower->setInteraction(QCP::iRangeZoom, !plotUpdateRealTIme);

    ui->plotVacuumRadiation->setInteraction(QCP::iRangeDrag, !plotUpdateRealTIme);
    ui->plotVacuumRadiation->setInteraction(QCP::iRangeZoom, !plotUpdateRealTIme);
}

void MainWindow::on_editRange_editingFinished()
{
    rangeDelta = ui->editRange->value();
    ui->plotEnergyCurrent->xAxis->setRange(now - rangeDelta, now);
}
