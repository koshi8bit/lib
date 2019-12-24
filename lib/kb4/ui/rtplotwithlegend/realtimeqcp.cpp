#include "realtimeqcp.h"
#include "ui_realtimeqcp.h"

RealTimeQCP::RealTimeQCP(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RealTimeQCP)
{
    ui->setupUi(this);

    configurePlot();
    configureLegend();

    connect(plot(), &QCustomPlot::axisClick, this, &RealTimeQCP::axisClick);
    connect(plot(), &QCustomPlot::axisDoubleClick, this, &RealTimeQCP::axisDoubleClick);

    connect(plot(), SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));
    //connect(plot(), &QCustomPlot::mouseMove, this, &RTPlotWithLegend::mouseMove);
    connect(plot(), &QCustomPlot::mousePress, this, &RealTimeQCP::mousePress);
    connect(plot(), &QCustomPlot::mouseDoubleClick, this, &RealTimeQCP::mouseDoubleClick);

    connect(plot(), &QCustomPlot::beforeReplot, this, &RealTimeQCP::beforeReplot);
    connect(plot()->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xAxisRangeChanged(QCPRange)));

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

void RealTimeQCP::setTimeAxisRange(int newRangeSEC)
{
    plot()->xAxis->setRangeLower(plot()->xAxis->range().upper - newRangeSEC);
    updateTimeAxisRangePostfix();
}

double RealTimeQCP::currentDateTime()
{
    auto time = QDateTime::currentDateTime();
    auto now = time.toTime_t() + static_cast<double>(time.time().msec())/1000;
    return now;
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

void RealTimeQCP::updateTimeAxisRangePostfix()
{
    auto delta = plot()->xAxis->range().upper - plot()->xAxis->range().lower;
    auto t = QTime(0, 0, 0).addSecs(static_cast<int>(delta));
    plot()->xAxis->setLabel(QString("%1 [%2]").arg(timeLabel).arg(t.toString(EasyLiving::formatTimeUi(false))));
}

void RealTimeQCP::configureLegend()
{
    _legendLayout = new QVBoxLayout(ui->scrollAreaLegend->widget());

    _labelTime = new QLabel(this);
    _labelTime->setText(timeLabel);
    _legendLayout->addWidget(_labelTime);

    auto spacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    _legendLayout->addItem(spacer);
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
