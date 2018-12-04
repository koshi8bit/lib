#include "mainwindow.h"
#include "ui_mainwindow.h"

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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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



