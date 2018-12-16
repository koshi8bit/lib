#include "rtplotwithlegend.h"
#include "ui_rtplotwithlegend.h"



RTPlotWithLegend::RTPlotWithLegend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RTPlotWithLegend)
{
    ui->setupUi(this);

    plot = ui->plot;

    configurePlotZoomAndDrag(plot, false);
    configurePlotBackground(plot);

    configurePlotTimeAxis(plot);
    configurePlotLine(plot);
    plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);

    connect(plot, &QCustomPlot::axisClick, this, &RTPlotWithLegend::axisClick);
    connect(plot, &QCustomPlot::axisDoubleClick, this, &RTPlotWithLegend::axisDoubleClick);
    connect(plot, &QCustomPlot::mouseMove, this, &RTPlotWithLegend::mouseMove);
}

RTPlotWithLegend::~RTPlotWithLegend()
{
    delete ui;
}

void RTPlotWithLegend::configurePlotZoomAndDrag(QCustomPlot *plot, bool zoomAndDragTimeAxis)
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

void RTPlotWithLegend::configurePlotBackground(QCustomPlot *plot)
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

void RTPlotWithLegend::configurePlotTimeAxis(QCustomPlot *plot)
{
    plot->xAxis->setLabel("Время");
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("hh:mm:ss.z");
    plot->xAxis->setTicker(dateTicker);
}

void RTPlotWithLegend::configurePlotLine(QCustomPlot *plot)
{
    line = new QCPItemLine(plot);
    auto pen = QPen();
    pen.setColor("#C0C0C0");
    pen.setStyle(Qt::PenStyle::DashDotLine);
    line->setPen(pen);
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

    //trassers

    auto lower = qMin(
                plot->yAxis->range().lower,
                plot->yAxis2->range().lower);

    auto upper = qMax(
                plot->yAxis->range().upper,
                plot->yAxis2->range().upper);

    line->start->setCoords(time, lower);
    line->end->setCoords(time, upper);
    //plot->replot();
}

void RTPlotWithLegend::setMarginGroup(QCPMarginGroup *mg)
{
    ui->plot->axisRect()->setMarginGroup(QCP::msLeft | QCP::msRight, mg);
}

void RTPlotWithLegend::setYAxisLabel(const QString &label)
{
    plot->yAxis->setLabel(label);
    plot->yAxis->setLabelPadding(20);
}

void RTPlotWithLegend::setYAxis2Label(const QString &label)
{
    plot->yAxis2->setVisible(true);
    plot->yAxis2->setLabelPadding(30);
    plot->yAxis2->setLabel(label);
}

QCustomPlot *RTPlotWithLegend::getPlot()
{
    return plot;
}
