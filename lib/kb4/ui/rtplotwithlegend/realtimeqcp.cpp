#include "realtimeqcp.h"
#include "ui_realtimeqcp.h"

RealTimeQCP::RealTimeQCP(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RealTimeQCP)
{
    ui->setupUi(this);

    configurePlot();
    configureLegend();
    //configureSplitter();

    connect(plot(), &QCustomPlot::axisClick, this, &RealTimeQCP::axisClick);
    connect(plot(), &QCustomPlot::axisDoubleClick, this, &RealTimeQCP::axisDoubleClick);

    connect(plot(), SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));
    //connect(plot(), &QCustomPlot::mouseMove, this, &RTPlotWithLegend::mouseMove);
    connect(plot(), &QCustomPlot::mousePress, this, &RealTimeQCP::mousePress);
    connect(plot(), &QCustomPlot::mouseDoubleClick, this, &RealTimeQCP::mouseDoubleClick);

    connect(plot(), &QCustomPlot::beforeReplot, this, &RealTimeQCP::beforeReplot);
    connect(plot()->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(timeAxisRangeChanged(QCPRange)));

}

RealTimeQCP::~RealTimeQCP()
{
    delete ui;
}

bool RealTimeQCP::realTime() const
{
    return _realTime;
}

void RealTimeQCP::configurePlot()
{
    setRealTime(true);

    setMoveLineRealTime(true);

    //WARNING dublicate configureAxesZoomAndDrag??
    ui->plot->setInteraction(QCP::iRangeZoom, true);
    ui->plot->setInteraction(QCP::iRangeDrag, true);

    //WARNING dublicate exec in setRealTime
    //configurePlotZoomAndDrag(false);

    configurePlotBackground();

    configurePlotTimeAxis();
    configurePlotLine();
    plot()->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);
    plot()->xAxis->setRangeUpper(RealTimeQCP::currentDateTime());
    setTimeAxisRange(90);

    // { Tests
    //plot()->setNoAntialiasingOnDrag(true);
    //plot()->setPlottingHint(QCP::phFastPolylines,true); // ?tima45 line from ethernet
    // } Tests
}


void RealTimeQCP::setRealTime(bool newValue)
{
    _realTime = newValue;
    configureAxesZoomAndDrag(!newValue);
}

bool RealTimeQCP::moveLineRealTime() const
{
    return _moveLineRealTime;
}

QCustomPlot *RealTimeQCP::plot() const
{
    return ui->plot;
}

void RealTimeQCP::moveTimeAxisRealTime()
{
//    auto range = plot()->xAxis->range();
//    auto delta = range.upper - range.lower;

    auto cdt = currentDateTime();

    plot()->xAxis->setRange(cdt - timeAxisOldRange, cdt);
}

void RealTimeQCP::setTimeAxisRange(int newRangeSEC)
{
    plot()->xAxis->setRangeLower(plot()->xAxis->range().upper - newRangeSEC);
    updateTimeAxisLabel();
}

void RealTimeQCP::setTimeLabelVisible(bool newValue)
{
    labelTime->setVisible(newValue);
}

void RealTimeQCP::setMarginGroup(QCPMarginGroup *mg)
{
    plot()->axisRect()->setMarginGroup(QCP::msLeft | QCP::msRight, mg);
}

double RealTimeQCP::currentDateTime()
{
    auto time = QDateTime::currentDateTime();
    auto now = time.toTime_t() + static_cast<double>(time.time().msec())/1000;
    return now;
}

void RealTimeQCP::configureAxis(QCPAxis *axis, const QString &label, const QString &postfix, double min, double max, QCPAxis::ScaleType scaleType, int precision)
{
    axis->setLabel(QString("%1 (%2)").arg(label).arg(postfix));
    axis->setVisible(true);
    axis->setRange(min, max);
    setAxisType(axis, scaleType);
    axis->setNumberPrecision(precision);
    //axis->setLabelPadding(20);

}

Graph *RealTimeQCP::addGraph(QCPAxis *axis, const QString &label, const QString &postfix, bool scientificNotation)
{
    auto graph = new Graph( label,
                            postfix,
                            colorSetter.getColor(),
                            plot(),
                            axis,
                            scientificNotation);

    graphs.append(graph);
    legendLayout->insertWidget(legendLayout->count()-1, graph->graphLegendItem());
    return graph;
}


void RealTimeQCP::setAxisType(QCPAxis *axis, QCPAxis::ScaleType scaleType)
{
    if (scaleType == QCPAxis::ScaleType::stLinear)
    {
        axis->setScaleType(QCPAxis::stLinear);
        QSharedPointer<QCPAxisTicker> ticker(new QCPAxisTicker);
        axis->setTicker(ticker);
        axis->setNumberFormat("f");
        axis->setNumberPrecision(1);
    }

    if (scaleType == QCPAxis::ScaleType::stLogarithmic)
    {
        axis->setScaleType(QCPAxis::stLogarithmic);
        QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
        axis->setTicker(logTicker);
        axis->setNumberFormat("eb");
        axis->setNumberPrecision(0);
    }
}


void RealTimeQCP::setMoveLineRealTime(bool moveLineRealTime)
{
    _moveLineRealTime = moveLineRealTime;
}


void RealTimeQCP::configureAxesZoomAndDrag(bool configureTimeAxis)
{
    auto axes = QList<QCPAxis*>()
            << plot()->yAxis
            << plot()->yAxis2;

    if (configureTimeAxis)
        axes << plot()->xAxis;


    plot()->axisRect()->setRangeZoomAxes(axes);
    plot()->axisRect()->setRangeDragAxes(axes);
}

void RealTimeQCP::configurePlotBackground()
{
    configurePlotBackgroundAxis(plot()->xAxis);
    configurePlotBackgroundAxis(plot()->yAxis);
    configurePlotBackgroundAxis(plot()->yAxis2);


    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    plot()->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(60, 60, 60));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    plot()->axisRect()->setBackground(axisRectGradient);
}

void RealTimeQCP::configurePlotBackgroundAxis(QCPAxis *axis)
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

void RealTimeQCP::configurePlotTimeAxis()
{
    plot()->xAxis->setLabel(timeLabel);
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("hh:mm:ss");
    plot()->xAxis->setTicker(dateTicker);
}

void RealTimeQCP::configurePlotLine()
{
    _line = new QCPItemLine(plot());
    auto pen = QPen();
    pen.setColor("#C0C0C0");
    pen.setStyle(Qt::PenStyle::DashLine);
    _line->setPen(pen);

    _line->start->setCoords(plot()->xAxis->range().upper, plot()->yAxis->range().upper);
    _line->end->setCoords(plot()->xAxis->range().upper, plot()->yAxis->range().lower);
}

void RealTimeQCP::updateTimeAxisLabel()
{
    auto delta = plot()->xAxis->range().upper - plot()->xAxis->range().lower;
    auto t = QTime(0, 0, 0).addSecs(static_cast<int>(delta));
    plot()->xAxis->setLabel(QString("%1 [%2]").arg(timeLabel).arg(t.toString(EasyLiving::formatTimeUi(false))));
}

void RealTimeQCP::configureLegend()
{
    legendLayout = new QVBoxLayout(ui->scrollAreaLegend->widget());

    labelTime = new QLabel(this);
    labelTime->setText(timeLabel);
    legendLayout->addWidget(labelTime);

    auto spacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    legendLayout->addItem(spacer);
}

void RealTimeQCP::configureSplitter()
{
    splitter = new QSplitter(Qt::Vertical, this);
    ui->horizontalLayout->insertWidget(1, splitter);
}

void RealTimeQCP::autoScaleAxis(QCPAxis *axis)
{
    axis->rescale(true);
    auto delta = (axis->range().upper - axis->range().lower)*0.05; // 5%
    axis->setRange(axis->range().lower - delta, axis->range().upper + delta);
}


void RealTimeQCP::axisClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event)
{
    Q_UNUSED(axis)
    Q_UNUSED(part)
    if (event->button() == Qt::MouseButton::RightButton)
    {
        autoScaleAxis(axis);
    }
}

void RealTimeQCP::axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event)
{
    Q_UNUSED(part)
    Q_UNUSED(event)
    if (event->button() == Qt::MouseButton::LeftButton)
    {
        auto plot = static_cast<QCustomPlot *>(sender());
        AxisConfig ac(axis, plot->xAxis == axis, this);
        ac.setModal(true);
        ac.exec();
    }
}

void RealTimeQCP::mouseMove(QMouseEvent *event)
{
    auto time = plot()->xAxis->pixelToCoord(event->x());
    mouseMove(time);
}

void RealTimeQCP::mousePress(QMouseEvent *event)
{
    if (isInAxisRect(event->pos()))
    {
        if (event->button() == Qt::MouseButton::RightButton)
        {
            auto newValue = !moveLineRealTime();
            setMoveLineRealTime(newValue);
            emit moveLineRealTimeChanged(newValue);
        }
    }
}

void RealTimeQCP::mouseDoubleClick(QMouseEvent *event)
{
    if (isInAxisRect(event->pos()))
    {
        if (event->button() == Qt::MouseButton::LeftButton)
        {
            auto newValue = !realTime();
            setRealTime(newValue);
            emit realTimeChanged(newValue);
            setMoveLineRealTime(newValue);
            emit moveLineRealTimeChanged(newValue);
        }
    }
}

void RealTimeQCP::beforeReplot()
{
    //WARNING update values without dependence of _line position
//    if (moveLineRealTime())
//    {
//        //BUG set to 1970 and don't move
//        mouseMove(RealTimeQCP::currentDateTime());
    //    }
}

void RealTimeQCP::timeAxisRangeChanged(const QCPRange &newRange)
{
    auto delta = newRange.upper - newRange.lower;
    if (!EasyLiving::isEqualDouble(timeAxisOldRange, delta))
    {
        timeAxisOldRange = delta;
        updateTimeAxisLabel();
    }
}


void RealTimeQCP::mouseMove(double time)
{
    //BUG ?is this mouse move or regular move by timer?
    if (labelTime->isVisible())
        labelTime->setText(formatLabelTime(time));

    foreach (auto graphElement, graphs)
    {
        graphElement->setGraphKey(time);
    }

    auto lower = qMin(
                plot()->yAxis->range().lower,
                plot()->yAxis2->range().lower);

    auto upper = qMax(
                plot()->yAxis->range().upper,
                plot()->yAxis2->range().upper);

    _line->start->setCoords(time, lower);
    _line->end->setCoords(time, upper);

    emit lineRealTimeMoved();

    //NOTE check cpu usage too big
//    if(!realTime())
//    {
//        plot()->replot();
//    }
}


QString RealTimeQCP::formatLabelTime(double time)
{
    //TODO show MSEC ?formatTimeUi(true)
    auto mouseTimeQDT = QDateTime::fromTime_t(static_cast<uint>(time));
    auto mouseTimeStr = mouseTimeQDT.toString(EasyLiving::formatTimeUi(true));

    auto deltaTimeMSEC = QDateTime::currentDateTime().msecsTo(mouseTimeQDT);
    //qDebug() << deltaTimeMSEC;
    if (deltaTimeMSEC > -1000)
        return mouseTimeStr;

    auto deltaTimeQT = QTime(0,0,0);
    deltaTimeQT = deltaTimeQT.addMSecs(static_cast<int>(-deltaTimeMSEC));
    auto deltaTimeStr = deltaTimeQT.toString(EasyLiving::formatTimeUi(true));


    return QString("%1 (-%2)").arg(mouseTimeStr).arg(deltaTimeStr);
}

bool RealTimeQCP::isInAxisRect(QPoint pos)
{
    return plot()->axisRect()->rect().contains(pos);
}
