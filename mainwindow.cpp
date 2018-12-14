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
    mg = new QCPMarginGroup(ui->plotHighVoltageCurrent);

    configurePlotEnergyCurrent();
    configurePlotTemperaturePower();
    configurePlotVacuumRadiation();
}


void MainWindow::configurePlotEnergyCurrent()
{
    configurePlot(ui->plotHighVoltageCurrent, "Энергия (кВ)", "Ток (мА)", mg);
    connect(ui->plotHighVoltageCurrent,SIGNAL(afterReplot()),ui->plotTemperaturePower,SLOT(replot()));
    connect(ui->plotHighVoltageCurrent,SIGNAL(afterReplot()),ui->plotVacuumRadiation,SLOT(replot()));
}

void MainWindow::configurePlotTemperaturePower()
{
    configurePlot(ui->plotTemperaturePower, "Температура (С)", "Мощность (Вт)", mg);
}


void MainWindow::configurePlotVacuumRadiation()
{
    configurePlot(ui->plotVacuumRadiation, "Вакуум (Пa)", "Радиация (Зв)", mg);
    ui->plotVacuumRadiation->yAxis->setScaleType(QCPAxis::stLogarithmic);
    QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
    ui->plotVacuumRadiation->yAxis->setTicker(logTicker);
    ui->plotVacuumRadiation->yAxis->setNumberFormat("eb");
    ui->plotVacuumRadiation->yAxis->setNumberPrecision(0);
}



void MainWindow::configurePlot(QCustomPlot *plot, const QString &y1Label, const QString &y2Label, QCPMarginGroup *mg)
{
    configurePlotZoomAndDrag(plot, false);
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

    plot->legend->setVisible(true);
    plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);

    //plot->setNoAntialiasingOnDrag(true);


    connect(plot->xAxis,SIGNAL(rangeChanged(QCPRange)),this,SLOT(changeRange(QCPRange)));
    //FIXME ?tima
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
        ui->plotHighVoltageCurrent->xAxis->setRange(now - plotScreenBufferSEC, now);
    }

    ui->plotHighVoltageCurrent->replot();
}



void MainWindow::configureGraphs()
{
    configureGraphsEnergyCurrent();

    configureGraphsTemperaturePower();

    configureGraphsVacuumRadiation();
}

void MainWindow::configureGraphsEnergyCurrent()
{
    //FIXME ?tima
    auto plot = ui->plotHighVoltageCurrent;
    auto xAxis = plot->xAxis;
    auto yAxis = plot->yAxis;
    auto yAxis2 = plot->yAxis2;

    ColorSetter cs(this);

    graphHighVoltageElvFull = plot->addGraph(xAxis, yAxis);
    graphHighVoltageElvFull->setName("ЭЛВ (полное напряжение)");
    graphHighVoltageElvFull->setPen(cs.getColor());

    graphHighVoltageElvFullTracer = new QCPItemTracer(plot);
    graphHighVoltageElvFullTracer->setGraph(graphHighVoltageElvFull);
    graphHighVoltageElvFullTracer->setGraphKey(5.5);
    graphHighVoltageElvFullTracer->setInterpolating(true);
    graphHighVoltageElvFullTracer->setStyle(QCPItemTracer::tsCircle);
    graphHighVoltageElvFullTracer->setPen(graphHighVoltageElvFull->pen());
    graphHighVoltageElvFullTracer->setBrush(graphHighVoltageElvFull->pen().color());
    graphHighVoltageElvFullTracer->setSize(7);



    graphHighVoltageElvFirstSection = plot->addGraph(xAxis, yAxis);
    graphHighVoltageElvFirstSection->setName("ЭЛВ (первая секция)");
    graphHighVoltageElvFirstSection->setPen(cs.getColor());

    graphCurrentBergozHebt = plot->addGraph(xAxis, yAxis2);
    graphCurrentBergozHebt->setName("Bergoz (выс. эн. тракт)");
    graphCurrentBergozHebt->setPen(cs.getColor());
}

void MainWindow::configureGraphsTemperaturePower()
{
    auto plot = ui->plotTemperaturePower;
    auto xAxis = plot->xAxis;
    auto yAxis = plot->yAxis;
    auto yAxis2 = plot->yAxis2;

    ColorSetter cs(this);

    graphTemperaturePyrometer = plot->addGraph(xAxis, yAxis);
    graphTemperaturePyrometer->setName("Пирометр");
    graphTemperaturePyrometer->setPen(cs.getColor());
}

void MainWindow::configureGraphsVacuumRadiation()
{
    auto plot = ui->plotVacuumRadiation;
    auto xAxis = plot->xAxis;
    auto yAxis = plot->yAxis;
    auto yAxis2 = plot->yAxis2;

    ColorSetter cs(this);

    graphVacuumTandem = plot->addGraph(xAxis, yAxis);
    graphVacuumTandem->setName("Тандем");
    graphVacuumTandem->setPen(cs.getColor());
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

    configurePlotZoomAndDrag(ui->plotHighVoltageCurrent, !plotUpdateRealTIme);
    configurePlotZoomAndDrag(ui->plotTemperaturePower, !plotUpdateRealTIme);
    configurePlotZoomAndDrag(ui->plotVacuumRadiation, !plotUpdateRealTIme);
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

void MainWindow::mouseMove(QMouseEvent *event)
{
    auto plot = static_cast<QCustomPlot*>(sender());
    auto time = plot->xAxis->pixelToCoord(event->x());
    graphHighVoltageElvFullTracer->setGraphKey(time);
}
