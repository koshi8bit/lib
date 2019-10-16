#include "rtplotwithlegend.h"
#include "ui_rtplotwithlegend.h"



RTPlotWithLegend::RTPlotWithLegend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RTPlotWithLegend)
{
    ui->setupUi(this);

    configurePlot();
    configureLegend();

    connect(_plot, &QCustomPlot::axisClick, this, &RTPlotWithLegend::axisClick);
    connect(_plot, &QCustomPlot::axisDoubleClick, this, &RTPlotWithLegend::axisDoubleClick);

    connect(_plot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));
    //connect(_plot, &QCustomPlot::mouseMove, this, &RTPlotWithLegend::mouseMove);
    connect(_plot, &QCustomPlot::beforeReplot, this, &RTPlotWithLegend::beforeReplot);
    connect(_plot, &QCustomPlot::mousePress, this, &RTPlotWithLegend::mousePress);
    connect(_plot, &QCustomPlot::mouseDoubleClick, this, &RTPlotWithLegend::mouseDoubleClick);

}

RTPlotWithLegend::~RTPlotWithLegend()
{
    _plot->deleteLater();
    line->deleteLater();

    //FIXME
//    foreach (auto graphElement, graphElements)
//        graphElement->deleteLater();

    delete ui;

}


void RTPlotWithLegend::configurePlot()
{
    _plot = ui->plot;

    setRealTime(true);

    setMoveLineRealTime(true);

    _plot->setInteraction(QCP::iRangeZoom, true);
    _plot->setInteraction(QCP::iRangeDrag, true);
    configurePlotZoomAndDrag(false);
    configurePlotBackground();

    configurePlotTimeAxis();
    configurePlotLine();
    _plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);
    auto _now = RTPlotWithLegend::now();
    _plot->xAxis->setRange(_now - 90, _now); //90=1min 30sec
    //_plot->setNoAntialiasingOnDrag(true);
    //_plot->setPlottingHint(QCP::phFastPolylines,true); // ?tima45 line from ethernet
}


void RTPlotWithLegend::configurePlotZoomAndDrag(bool zoomAndDragTimeAxis)
{
    auto axes = QList<QCPAxis*>()
            << _plot->yAxis
            << _plot->yAxis2;

    if (zoomAndDragTimeAxis)
        axes << _plot->xAxis;


    _plot->axisRect()->setRangeZoomAxes(axes);
    _plot->axisRect()->setRangeDragAxes(axes);


//    _plot->setInteraction(QCP::iRangeZoom, zoomAndDragTimeAxis);
//    _plot->setInteraction(QCP::iRangeDrag, zoomAndDragTimeAxis);
//    if (zoomAndDragTimeAxis)
//    {
//        auto axes = QList<QCPAxis*>()
//                << _plot->xAxis
//                << _plot->yAxis
//                << _plot->yAxis2;

//        _plot->axisRect()->setRangeZoomAxes(axes);
//        _plot->axisRect()->setRangeDragAxes(axes);
//    }
}

bool RTPlotWithLegend::realTime()
{
    return _realTime;
}

double RTPlotWithLegend::timeAxisRangeSEC()
{
    auto range = _plot->xAxis->range();
    return range.upper - range.lower;

}

void RTPlotWithLegend::setNumberPrecision(RTPlotWithLegend::Axis axis, int newValue)
{
    auto _axis = getAxis(axis);
    _axis->setNumberPrecision(newValue);
}

void RTPlotWithLegend::setRealTime(bool newValue)
{
    _realTime = newValue;
    configurePlotZoomAndDrag(!newValue);
}

void RTPlotWithLegend::setMoveLineRealTime(bool newValue)
{
    _moveLineRealTime = newValue;
}

bool RTPlotWithLegend::moveLineRealTime()
{
    return _moveLineRealTime;
}


Graph *RTPlotWithLegend::addGraph(RTPlotWithLegend::Axis axis, const QString &label, const QString &postfix, bool scientificNotation)
{

    auto graphElement = new Graph(label,
                            postfix,
                            colorSetter.getColor(),
                            _plot,
                            getAxis(axis),
                            scientificNotation,
                            this);

    graphElements.append(graphElement);
    legendLayout->insertWidget(legendLayout->count()-1, graphElement->graphLegendItem());
    return graphElement;
}



void RTPlotWithLegend::configurePlotBackground()
{
    configurePlotBackgroundAxis(_plot->xAxis);
    configurePlotBackgroundAxis(_plot->yAxis);
    configurePlotBackgroundAxis(_plot->yAxis2);


    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    _plot->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(60, 60, 60));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    _plot->axisRect()->setBackground(axisRectGradient);
}

void RTPlotWithLegend::configurePlotBackgroundAxis(QCPAxis *axis)
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

void RTPlotWithLegend::configurePlotTimeAxis()
{
    _plot->xAxis->setLabel("Время");
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("hh:mm:ss");
    _plot->xAxis->setTicker(dateTicker);
}

void RTPlotWithLegend::configurePlotLine()
{
    line = new QCPItemLine(_plot);
    auto pen = QPen();
    pen.setColor("#C0C0C0");
    pen.setStyle(Qt::PenStyle::DashLine);
    line->setPen(pen);

    line->start->setCoords(_plot->xAxis->range().upper, _plot->yAxis->range().upper);
    line->end->setCoords(_plot->xAxis->range().upper, _plot->yAxis->range().lower);
}

void RTPlotWithLegend::configureLegend()
{
    legendLayout = new QVBoxLayout(ui->scrollAreaLegend->widget());

    labelTime = new QLabel(this);
    labelTime->setText("time");
    legendLayout->addWidget(labelTime);

    auto spacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    legendLayout->addItem(spacer);

}

QCPAxis *RTPlotWithLegend::getAxis(RTPlotWithLegend::Axis axis)
{
    QCPAxis *result = _plot->yAxis;
    if (axis == Axis::yAxisL)
        result = _plot->yAxis;

    if (axis == Axis::yAxisR)
        result = _plot->yAxis2;

    return result;

}

void RTPlotWithLegend::rescale(QCPAxis *axis)
{
    axis->rescale(true);
    auto delta = (axis->range().upper - axis->range().lower)*0.05; // 5%
    axis->setRange(axis->range().lower - delta, axis->range().upper + delta);
}

void RTPlotWithLegend::axisClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event)
{
    Q_UNUSED(axis)
    Q_UNUSED(part)
    if (event->button() == Qt::MouseButton::RightButton)
    {
        rescale(axis);
    }
}

void RTPlotWithLegend::axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event)
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

void RTPlotWithLegend::mousePress(QMouseEvent *event)
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

void RTPlotWithLegend::mouseDoubleClick(QMouseEvent *event)
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

bool RTPlotWithLegend::isInAxisRect(QPoint pos)
{
    return _plot->axisRect()->rect().contains(pos);
}

void RTPlotWithLegend::beforeReplot()
{
    if (moveLineRealTime())
    {
        //BUG set to 1970 and don't move
        mouseMove(RTPlotWithLegend::now());
    }
}


void RTPlotWithLegend::mouseMove(QMouseEvent *event)
{
    auto plot = static_cast<QCustomPlot*>(sender());

    auto time = plot->xAxis->pixelToCoord(event->x());
    mouseMove(time);
}


void RTPlotWithLegend::mouseMove(double time)
{

    auto plot = this->_plot;

    //BUG ?is this mouse move or regular move by timer?
    if (labelTime->isVisible())
        labelTime->setText(getDateTime(time));

    foreach (auto graphElement, graphElements)
    {
        graphElement->setGraphKey(time);
    }

    auto lower = qMin(
                plot->yAxis->range().lower,
                plot->yAxis2->range().lower);

    auto upper = qMax(
                plot->yAxis->range().upper,
                plot->yAxis2->range().upper);

    line->start->setCoords(time, lower);
    line->end->setCoords(time, upper);

    emit lineRealTimeMoved();

    //NOTE check cpu usage too big
    //plot->replot();
}

void RTPlotWithLegend::setMarginGroup(QCPMarginGroup *mg)
{
    _plot->axisRect()->setMarginGroup(QCP::msLeft | QCP::msRight, mg);
}

void RTPlotWithLegend::configureAxis(RTPlotWithLegend::Axis axis, const QString &label, double min, double max, QCPAxis::ScaleType scaleType)
{

    auto _axis = RTPlotWithLegend::getAxis(axis);
    _axis->setVisible(true);
    _axis->setLabel(label);
    _axis->setRange(min, max);
    //axis->setLabelPadding(20);

    setAxisType(_axis, scaleType);
}

void RTPlotWithLegend::setAxisType(QCPAxis *axis, QCPAxis::ScaleType scaleType)
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

QCustomPlot *RTPlotWithLegend::plot()
{
    return _plot;
}

double RTPlotWithLegend::now()
{
    auto time = QDateTime::currentDateTime();
    auto now = time.toTime_t() + static_cast<double>(time.time().msec())/1000;
    return now;
}

QString RTPlotWithLegend::getDateTime(double time)
{
    //TODO show MSEC ?formatTimeUi(true)
    auto mouseTimeQDT = QDateTime::fromTime_t(static_cast<uint>(time));
    auto mouseTimeStr = mouseTimeQDT.toString(EasyLiving::formatTimeUi(false));

    auto deltaTimeMSEC = QDateTime::currentDateTime().msecsTo(mouseTimeQDT);
    qDebug() << deltaTimeMSEC;
    if (deltaTimeMSEC > -1000)
        return mouseTimeStr;

    auto deltaTimeQT = QTime(0,0,0);
    deltaTimeQT = deltaTimeQT.addMSecs(static_cast<int>(-deltaTimeMSEC));
    auto deltaTimeStr = deltaTimeQT.toString(EasyLiving::formatTimeUi(false));


    return QString("%1 (-%2)").arg(mouseTimeStr).arg(deltaTimeStr);
}

void RTPlotWithLegend::setLabelTimeVisible(bool newValue)
{
    labelTime->setVisible(newValue);
}
