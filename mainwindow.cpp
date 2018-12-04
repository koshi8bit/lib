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
    connect(timer, SIGNAL(timeout()), this, SLOT(drawData()));
    timer->start(100);
}

void MainWindow::configurePlotEnergyCurrent(QCustomPlot *plot, const QString &y1Label, const QString &y2Label)
{
    plot->xAxis->setLabel("Время");

    plot->yAxis->setLabel(y1Label);

    plot->yAxis2->setVisible(true);
    plot->yAxis2->setLabel(y2Label);

    plot->setInteraction(QCP::iRangeDrag, true);
    plot->setInteraction(QCP::iRangeZoom, true);

    connect(plot->xAxis,SIGNAL(rangeChanged(QCPRange)),this,SLOT(changeRanges(QCPRange)));


    plot->xAxis->setDateTimeFormat("hh:mm:ss");
    plot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
}

void MainWindow::drawData()
{
    auto date = QDateTime::currentDateTime().toTime_t();
    graphEnergy->addData(date, sin(date));

    if (ui->checkBox->isChecked())
        ui->plotEnergyCurrent->xAxis->setRange(date - plotScreenBufferSEC, date);
    ui->plotEnergyCurrent->replot();
}

void MainWindow::configureGraphEnergyCurrent()
{
    graphEnergy = ui->plotEnergyCurrent->addGraph();
    graphEnergy->setPen(QColor(0xAA, 0xBB, 0xCC));

    graphCurrent = ui->plotEnergyCurrent->addGraph();
    graphCurrent->setPen(QColor(0x0A, 0x0B, 0x0C));
}

void MainWindow::configureGraph()
{
    configureGraphEnergyCurrent();

    graphTemperature = ui->plotTemperaturePower->addGraph();
    graphTemperature->setPen(QColor(0xAA, 0xBB, 0xCC));
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

void MainWindow::changeRanges(QCPRange range)
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
