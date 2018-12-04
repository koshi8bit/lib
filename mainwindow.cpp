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

void MainWindow::configurePlotEnergyCurrent(QCustomPlot *plot, const QString &y1Label, const QString &y2Label)
{
    configurePlotBackground(plot);

    plot->xAxis->setLabel("Время");

    plot->yAxis->setLabel(y1Label);

    plot->yAxis2->setVisible(true);
    plot->yAxis2->setLabel(y2Label);

    plot->setInteraction(QCP::iRangeDrag, true);
    plot->setInteraction(QCP::iRangeZoom, true);

    connect(plot->xAxis,SIGNAL(rangeChanged(QCPRange)),this,SLOT(changeRange(QCPRange)));


    plot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    plot->xAxis->setDateTimeFormat("hh:mm:ss.z");

    plot->axisRect()->setRangeZoom(Qt::Horizontal);
    plot->axisRect()->setRangeDrag(Qt::Horizontal);
}

void MainWindow::drawData()
{
    auto now = QDateTime::currentDateTime();
    auto time = now.toTime_t() + static_cast<double>(now.time().msec())/1000;


    graphEnergy->addData(time, sin(time));
    graphTemperature->addData(time, QRandomGenerator::global()->bounded(1.0));

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
}

void MainWindow::configureGraph()
{
    configureGraphEnergyCurrent();

    graphTemperature = ui->plotTemperaturePower->addGraph();
    graphTemperature->setPen(QColor(255, 255, 255));
}

void MainWindow::configurePlot()
{
    configurePlotEnergyCurrent(ui->plotEnergyCurrent, "Энергия (кВ)", "Ток (мА)");
    configurePlotEnergyCurrent(ui->plotTemperaturePower, "Температура (С)", "Мощность (Вт)");
    configurePlotEnergyCurrent(ui->plotVacuumRadiation, "Вакуум (Pa)", "Радиация (Зв)");

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
}
