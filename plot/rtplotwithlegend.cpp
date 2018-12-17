#include "rtplotwithlegend.h"
#include "ui_rtplotwithlegend.h"



RTPlotWithLegend::RTPlotWithLegend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RTPlotWithLegend)
{
    ui->setupUi(this);

    _plot = ui->plot;

    configurePlotZoomAndDrag(false);
    configurePlotBackground();

    configurePlotTimeAxis();
    configurePlotLine();
    _plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);
    //plot->setNoAntialiasingOnDrag(true);

    configureLegend();

    connect(_plot, &QCustomPlot::axisClick, this, &RTPlotWithLegend::axisClick);
    connect(_plot, &QCustomPlot::axisDoubleClick, this, &RTPlotWithLegend::axisDoubleClick);
    //FIXME tima signal
    connect(_plot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));
    //connect(_plot, &QCustomPlot::mouseMove(QMouseEvent *), this, &RTPlotWithLegend::mouseMove(QMouseEvent *));
}

RTPlotWithLegend::~RTPlotWithLegend()
{
    _plot->deleteLater();
    line->deleteLater();

//    foreach (auto graphElement, graphElements)
//        graphElement->deleteLater();

    delete ui;

}

void RTPlotWithLegend::configurePlotZoomAndDrag(bool zoomAndDragTimeAxis)
{
    auto axes = QList<QCPAxis*>()
            << _plot->yAxis
            << _plot->yAxis2;

    if (zoomAndDragTimeAxis)
        axes << _plot->xAxis;

    _plot->setInteraction(QCP::iRangeZoom, true);
    _plot->setInteraction(QCP::iRangeDrag, true);
    _plot->axisRect()->setRangeZoomAxes(axes);
    _plot->axisRect()->setRangeDragAxes(axes);
}

GraphElement *RTPlotWithLegend::addGraph(RTPlotWithLegend::Axis axis, const QString &label)
{

    auto graphElement = new GraphElement(label,
                            colorSetter.getColor(),
                            _plot,
                            getAxis(axis),
                            this);

    graphElements.append(graphElement);
    legendLayout->addWidget(graphElement->graphLegendItem());
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

}

QCPAxis *RTPlotWithLegend::getAxis(RTPlotWithLegend::Axis axis)
{
    QCPAxis *result = _plot->yAxis;
    if (axis == Axis::yAxis)
        result = _plot->yAxis;

    if (axis == Axis::yAxis2)
        result = _plot->yAxis2;

    return result;

}

void RTPlotWithLegend::axisClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event)
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

void RTPlotWithLegend::axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event)
{
    auto plot = static_cast<QCustomPlot *>(sender());
    AxisConfig ac(axis, plot->xAxis == axis, this);
    ac.setModal(true);
    ac.exec();

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
    //NOTE check cpu usage too big
    //plot->replot();
}

void RTPlotWithLegend::setMarginGroup(QCPMarginGroup *mg)
{
    _plot->axisRect()->setMarginGroup(QCP::msLeft | QCP::msRight, mg);
}

void RTPlotWithLegend::setAxisLabel(RTPlotWithLegend::Axis axis, const QString &label, QCPAxis::ScaleType scaleType)
{

    auto _axis = RTPlotWithLegend::getAxis(axis);
    _axis->setVisible(true);
    _axis->setLabel(label);
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
