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
    //connect(ui->rtPlotHighVoltageCurrent->getPlot(), SIGNAL(afterReplot()), ui->plotTemperaturePower, SLOT(replot()));
    //connect(ui->rtPlotHighVoltageCurrent->getPlot(), SIGNAL(afterReplot()), ui->plotVacuumRadiation, SLOT(replot()));

    ui->rtPlotTemperaturePower->setAxisLabel(RTPlotWithLegend::Axis::yAxis, "Температура (С)");
    ui->rtPlotTemperaturePower->setAxisLabel(RTPlotWithLegend::Axis::yAxis2, "Мощность (Вт)");
    ui->rtPlotTemperaturePower->setMarginGroup(mg);

    ui->rtPlotVacuumRadiation->setAxisLabel(RTPlotWithLegend::Axis::yAxis, "Вакуум (Пa)", QCPAxis::ScaleType::stLogarithmic);
    ui->rtPlotVacuumRadiation->setAxisLabel(RTPlotWithLegend::Axis::yAxis2, "Радиация (Зв)");
    ui->rtPlotVacuumRadiation->setMarginGroup(mg);
}


void MainWindow::configurePlot(QCustomPlot *plot, const QString &y1Label, const QString &y2Label, QCPMarginGroup *mg, QCPItemLine **line)
{
    configurePlotZoomAndDrag(plot, false);
    configurePlotBackground(plot);

    plot->xAxis->setLabel("Время");
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("hh:mm:ss");
    plot->xAxis->setTicker(dateTicker);

    plot->yAxis->setLabel(y1Label);
    plot->yAxis->setLabelPadding(20);

    plot->yAxis2->setVisible(true);
    plot->yAxis2->setLabelPadding(30);
    plot->yAxis2->setLabel(y2Label);

    plot->axisRect()->setMarginGroup(QCP::msLeft | QCP::msRight, mg);

    plot->legend->setVisible(true);
    plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);

    //plot->setNoAntialiasingOnDrag(true);

    *line = new QCPItemLine(plot);
    auto pen = QPen();
    pen.setColor("#C0C0C0");
    pen.setStyle(Qt::PenStyle::DashDotLine);
    auto tmp = *line;
    tmp->setPen(pen);

    connect(plot->xAxis,SIGNAL(rangeChanged(QCPRange)),this,SLOT(changeRange(QCPRange)));
    //FIXME ?tima connect
    //connect(plot->xAxis, &QCPAxis::rangeChanged, this, &MainWindow::changeRange);
    connect(plot, &QCustomPlot::axisClick, this, &MainWindow::axisClick);
    connect(plot, &QCustomPlot::axisDoubleClick, this, &MainWindow::axisDoubleClick);
    connect(plot, &QCustomPlot::mouseMove, this, &MainWindow::mouseMove);
}

void MainWindow::configurePlotZoomAndDrag(QCustomPlot *plot, bool zoomAndDragTimeAxis)
{
    auto axes = QList<QCPAxis*>()
            << plot->yAxis
            << plot->yAxis2;

    if (zoomAndDragTimeAxis)
        axes << plot->xAxis;

    plot->setInteraction(QCP::iRangeZoom, true);
    plot->setInteraction(QCP::iRangeDrag, true);
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

    graphHighVoltageElvFull->addData(now, sin(5.0f/2*cos(now)));
    graphHighVoltageElvFirstSection->addData(now, sin(now));
    graphCurrentBergozHebt->addData(now, QRandomGenerator::global()->bounded(1.0));
    graphTemperaturePyrometer->addData(now, sin(9.0f/2*cos(now)));
    graphVacuumTandem->addData(now, qPow(qSin(now), 2) - 2*qSin(now) - 2);


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

    if(axis != ui->plotHighVoltageCurrent->xAxis)
        ui->plotHighVoltageCurrent->xAxis->setRange(range);
    if(axis != ui->plotTemperaturePower->xAxis)
        ui->plotTemperaturePower->xAxis->setRange(range);
    if(axis != ui->plotVacuumRadiation->xAxis)
        ui->plotVacuumRadiation->xAxis->setRange(range);

    plotScreenBufferSEC = range.upper - range.lower;

    ui->plotHighVoltageCurrent->replot();
}





void MainWindow::on_checkBoxRealTime_stateChanged(int arg1)
{
    plotUpdateRealTIme = static_cast<bool>(arg1);

    ui->rtPlotHighVoltageCurrent->configurePlotZoomAndDrag(!plotUpdateRealTIme);
    ui->rtPlotTemperaturePower->configurePlotZoomAndDrag(!plotUpdateRealTIme);
    ui->rtPlotVacuumRadiation->configurePlotZoomAndDrag(!plotUpdateRealTIme);
}


void MainWindow::axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event)
{
    auto plot = static_cast<QCustomPlot *>(sender());
    AxisConfig ac(axis, plot->xAxis == axis, this);
    ac.setModal(true);
    ac.exec();
}

void MainWindow::axisClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event)
{
    qDebug() << event;
    if (event->button() == Qt::RightButton)
    {
        foreach(auto graph, axis->graphs())
        {
            graph->rescaleValueAxis(false, true);
        }
    }
}

//void MainWindow::mouseMove(QMouseEvent *event)
//{
//    auto plot = static_cast<QCustomPlot*>(sender());
//    auto time = plot->xAxis->pixelToCoord(event->x());
//    tracerHighVoltageElvFull->setGraphKey(time);
//    tracerHighVoltageElvFirstSection->setGraphKey(time);

//    auto lower = qMin(
//                ui->plotHighVoltageCurrent->yAxis->range().lower,
//                ui->plotHighVoltageCurrent->yAxis2->range().lower);

//    auto upper = qMax(
//                ui->plotHighVoltageCurrent->yAxis->range().upper,
//                ui->plotHighVoltageCurrent->yAxis2->range().upper);


//    lineHighVoltageCurrent->start->setCoords(time, lower);
//    lineHighVoltageCurrent->end->setCoords(time, upper);


//    auto lower1 = qMin(
//                ui->plotTemperaturePower->yAxis->range().lower,
//                ui->plotTemperaturePower->yAxis2->range().lower);

//    auto upper1 = qMax(
//                ui->plotTemperaturePower->yAxis->range().upper,
//                ui->plotTemperaturePower->yAxis2->range().upper);


//    lineTemperaturePower->start->setCoords(time, lower1);
//    lineTemperaturePower->end->setCoords(time, upper1);
//}
