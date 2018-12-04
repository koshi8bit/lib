#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    configurePlot();
    configureGraph();

    timer = new QTimer(this);
    timer->setInterval(plotUpdateIntervalMSEC);
    connect(timer, SIGNAL(timeout()), this, SLOT(drawData()));
    timer->start();
}

void MainWindow::configurePlotAxis(QCPAxis *axis)
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

void MainWindow::configurePlotBackground(QCustomPlot *plot)
{
    configurePlotAxis(plot->xAxis);
    configurePlotAxis(plot->yAxis);
    configurePlotAxis(plot->yAxis2);

    plot->axisRect()->setRangeDrag(Qt::Horizontal);
    plot->axisRect()->setRangeZoom(Qt::Horizontal);


    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    plot->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(80, 80, 80));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    plot->axisRect()->setBackground(axisRectGradient);
}

void MainWindow::configurePlotLabel(QCustomPlot *plot, const QString &y1Label, const QString &y2Label)
{
    configurePlotBackground(plot);

    plot->xAxis->setLabel("Время");

    plot->yAxis->setLabel(y1Label);
    plot->yAxis->setLabelPadding(20);

    plot->yAxis2->setVisible(true);
    plot->yAxis2->setLabelPadding(30);
    plot->yAxis2->setLabel(y2Label);

    plot->setNoAntialiasingOnDrag(true);


    connect(plot->xAxis,SIGNAL(rangeChanged(QCPRange)),this,SLOT(changeRange(QCPRange)));
    connect(plot->xAxis,SIGNAL(rangeChanged(QCPRange)),this,SLOT(changeRange(QCPRange)));
}

void MainWindow::drawData()
{
    auto now = QDateTime::currentDateTime();
    auto time = now.toTime_t() + static_cast<double>(now.time().msec())/1000;


    graphEnergy->addData(time, sin(time));
    graphTemperature->addData(time, QRandomGenerator::global()->bounded(1.0));
    graphCurrent->addData(time, cos(time)*1000);

    if (ui->checkBox->isChecked())
        ui->plotEnergyCurrent->xAxis->setRange(time - plotScreenBufferSEC, time);
    ui->plotEnergyCurrent->replot();
}

void MainWindow::configureGraphEnergyCurrent()
{
    graphEnergy = ui->plotEnergyCurrent->addGraph();
    graphEnergy->setPen(QColor(255, 255, 255));

    graphCurrent = ui->plotEnergyCurrent->addGraph();
    graphCurrent->setPen(QColor(255, 66, 66));
    //graphCurrent->
}

void MainWindow::configureGraph()
{
    configureGraphEnergyCurrent();

    graphTemperature = ui->plotTemperaturePower->addGraph();
    graphTemperature->setPen(QColor(255, 255, 255));
}

void MainWindow::configurePlot()
{
    configurePlotLabel(ui->plotEnergyCurrent, "Энергия (кВ)", "Ток (мА)");

    configurePlotLabel(ui->plotTemperaturePower, "Температура (С)", "Мощность (Вт)");

    configurePlotLabel(ui->plotVacuumRadiation, "Вакуум (Пa)", "Радиация (Зв)");
    ui->plotVacuumRadiation->yAxis->setScaleType(QCPAxis::stLogarithmic);
//    QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
//    ui->plotVacuumRadiation->yAxis->setTicker(logTicker);

    connect(ui->plotEnergyCurrent,SIGNAL(afterReplot()),ui->plotTemperaturePower,SLOT(replot()));
    connect(ui->plotEnergyCurrent,SIGNAL(afterReplot()),ui->plotVacuumRadiation,SLOT(replot()));

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeRange(QCPRange range)
{
    QCPAxis* axis = (QCPAxis*)QObject::sender();

    if(axis != ui->plotEnergyCurrent->xAxis)
        ui->plotEnergyCurrent->xAxis->setRange(range);
    if(axis != ui->plotTemperaturePower->xAxis)
        ui->plotTemperaturePower->xAxis->setRange(range);
    if(axis != ui->plotVacuumRadiation->xAxis)
        ui->plotVacuumRadiation->xAxis->setRange(range);
}




void MainWindow::on_checkBox_stateChanged(int arg1)
{
    plotUpdateRealTIme = static_cast<bool>(arg1);

    ui->plotEnergyCurrent->setInteraction(QCP::iRangeDrag, !plotUpdateRealTIme);
    ui->plotEnergyCurrent->setInteraction(QCP::iRangeZoom, !plotUpdateRealTIme);

    ui->plotTemperaturePower->setInteraction(QCP::iRangeDrag, !plotUpdateRealTIme);
    ui->plotTemperaturePower->setInteraction(QCP::iRangeZoom, !plotUpdateRealTIme);

    ui->plotVacuumRadiation->setInteraction(QCP::iRangeDrag, !plotUpdateRealTIme);
    ui->plotVacuumRadiation->setInteraction(QCP::iRangeZoom, !plotUpdateRealTIme);

}
