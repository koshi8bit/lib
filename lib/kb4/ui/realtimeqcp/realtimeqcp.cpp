#include "realtimeqcp.h"
#include "ui_realtimeqcp.h"

RealTimeQCP::RealTimeQCP(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RealTimeQCP)
{
    ui->setupUi(this);

    connect(plot(), &QCustomPlot::axisClick, this, &RealTimeQCP::axisClick);
    connect(plot(), &QCustomPlot::axisDoubleClick, this, &RealTimeQCP::axisDoubleClick);

    //connect(plot(), &QCustomPlot::mouseMove, this, &RTPlotWithLegend::mouseMove);
    connect(plot(), SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));
    connect(plot(), &QCustomPlot::mousePress, this, &RealTimeQCP::mousePress);
    connect(plot(), &QCustomPlot::mouseDoubleClick, this, &RealTimeQCP::mouseDoubleClick);

    connect(plot(), &QCustomPlot::beforeReplot, this, &RealTimeQCP::beforeReplot);
    connect(plot()->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(setTimeAxisRange(QCPRange)));

    configurePlot();
    configureLegend();
    _setCursor2Visible(false);
    //configureSplitter();

}

RealTimeQCP::~RealTimeQCP()
{
    //FIXME "FTH: (8440): *** Fault tolerant heap.."
    delete ui;
}

bool RealTimeQCP::realTime() const
{
    return _realTime;
}

void RealTimeQCP::configurePlot()
{


    //WARNING dublicate configureAxesZoomAndDrag??
    ui->plot->setInteraction(QCP::iRangeZoom, true);
    ui->plot->setInteraction(QCP::iRangeDrag, true);

    setRealTime(true);

    //WARNING dublicate exec in setRealTime
    //configureAxesZoomAndDrag(false);

    configurePlotBackground();

    configurePlotTimeAxis();
    configurePlotLine();
    setMoveLineRealTime(true);
    plot()->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);
    plot()->xAxis->setRangeUpper(RealTimeQCP::currentDateTime());
    setTimeAxisRange(90);

    // { Tests
    //plot()->setNoAntialiasingOnDrag(true);
    //plot()->setPlottingHint(QCP::phFastPolylines,true); // ?tima45 line from ethernet
    // } Tests
}


void RealTimeQCP::_setRealTime(bool newValue)
{
    _realTime = newValue;
    configureAxesZoomAndDrag(!newValue);
}

void RealTimeQCP::setRealTime(bool newValue)
{
    _setRealTime(newValue);
    emit realTimeChanged(newValue);
}

void RealTimeQCP::setCursor2Visible(bool newValue)
{
    _setCursor2Visible(newValue);
    emit cursor2VisibleValueChanged(newValue);
}

void RealTimeQCP::setCursor2Key(double key)
{
    _setCursor2Key(key);
    emit cursor2KeyChanged(key);
}

void RealTimeQCP::setTimeAxisRange(const QCPRange &newValue)
{
    _setTimeAxisRange(newValue);
    emit timeAxisRangeChanged(newValue);
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

    if (realTime())
    {
        auto cdt = currentDateTime();

        plot()->xAxis->setRange(cdt - timeAxisOldRange, cdt);
    }
    plot()->replot();
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

void RealTimeQCP::configureAxis(QCPAxis *axis, const QString &label, const QString &postfix, double min, double max, int precision, QCPAxis::ScaleType scaleType)
{
    if (postfix.isEmpty())
    {
        axis->setLabel(label);
    }
    else
    {
        axis->setLabel(QString("%1 (%2)").arg(label).arg(postfix));
    }
    axis->setVisible(true);
    axis->setRange(min, max);
    setAxisType(axis, scaleType);
    axis->setNumberPrecision(precision);
    //axis->setLabelPadding(20);

}

Graph *RealTimeQCP::addGraph(const QString &label, const QString &postfix, int precision, bool scientificNotation)
{
    return addGraph(plot()->yAxis, label, postfix, precision, scientificNotation);
}

Graph *RealTimeQCP::addGraph(QCPAxis *axis, const QString &label, const QString &postfix, int precision, bool scientificNotation)
{
    auto graph = new Graph( label,
                            postfix,
                            colorSetter.getColor(),
                            plot(),
                            axis,
                            precision,
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

void RealTimeQCP::_setCursor2Visible(bool newValue)
{
    _cursor2->setVisible(newValue);
    foreach (auto graphElement, graphs)
    {
        graphElement->setCursor2Visible(newValue);
    }

    if (labelTime->isVisible())
        labelTime->setText(formatLabelTime(_cursor->start->key()));
}

void RealTimeQCP::_setCursor2Key(double key)
{
    foreach (auto graphElement, graphs)
    {
        graphElement->moveCursor2(_cursor->start->key());
    }

    _cursor2->start->setCoords(key, _cursor->start->coords().y());
    _cursor2->end->setCoords(key, _cursor->end->coords().y());
    _setCursor2Visible(true);
    plot()->replot();
}

double RealTimeQCP::getYAxisUpper()
{
    return qMax(plot()->yAxis->range().upper,
                plot()->yAxis2->range().upper);
}

double RealTimeQCP::getYAxisLower()
{
    return qMin(plot()->yAxis->range().lower,
                plot()->yAxis2->range().lower);

}

bool RealTimeQCP::cursor2Visible()
{
    return _cursor2->visible();
}


void RealTimeQCP::setCursor2Visible(bool newValue, RealTimeQCP *senderWidget)
{
    if (senderWidget == this) { return; }

    _setCursor2Visible(newValue);
}

void RealTimeQCP::setCursor2Key(double key, RealTimeQCP *senderWidget)
{
    if (senderWidget == this) { return; }

    _setCursor2Key(key);
}

void RealTimeQCP::setMoveLineRealTime(bool newValue, RealTimeQCP *senderWidget)
{
    if (senderWidget == this) { return; }

    _setMoveLineRealTime(newValue);
}

void RealTimeQCP::setRealTime(bool newValue, RealTimeQCP *senderWidget)
{
    if (senderWidget == this) { return; }

    _setRealTime(newValue);
}

void RealTimeQCP::setCursorKey(double key, RealTimeQCP *senderWidget)
{
    if (senderWidget == this) { return; }

    _setCursorKey(key);
}

void RealTimeQCP::setTimeAxisRange(const QCPRange &newRange, RealTimeQCP *senderWidget)
{
    if (senderWidget == this) { return; }

    _setTimeAxisRange(newRange);
}


void RealTimeQCP::_setMoveLineRealTime(bool newValue)
{
    _moveLineRealTime = newValue;
}

void RealTimeQCP::setMoveLineRealTime(bool newValue)
{
    _setMoveLineRealTime(newValue);
    emit moveLineRealTimeChanged(newValue);
}


void RealTimeQCP::configureAxesZoomAndDrag(bool configureTimeAxis)
{
    auto axes = QList<QCPAxis*>()
            << plot()->yAxis
            << plot()->yAxis2;

    Q_UNUSED(configureTimeAxis)
    //if (configureTimeAxis)
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
    configurePlotLine(&_cursor);
    configurePlotLine(&_cursor2);
}

void RealTimeQCP::configurePlotLine(QCPItemLine **line)
{
    (*line) = new QCPItemLine(plot());
    auto pen = QPen();
    pen.setColor("#C0C0C0");
    pen.setStyle(Qt::PenStyle::DashLine);
    (*line)->setPen(pen);

    (*line)->start->setCoords(plot()->xAxis->range().upper, plot()->yAxis->range().upper);
    (*line)->end->setCoords(plot()->xAxis->range().upper, plot()->yAxis->range().lower);
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
    setCursorKey(time);
}

void RealTimeQCP::mousePress(QMouseEvent *event)
{
    if (isInAxisRect(event->pos()))
    {
        if (event->button() == Qt::MouseButton::RightButton)
        {
            setMoveLineRealTime(!moveLineRealTime());
        }

        if (event->button() == Qt::MouseButton::MiddleButton)
        {
            if (!cursor2Visible())
            {
                setCursor2Key(_cursor->start->key());
            }
            else
            {
                setCursor2Visible(false);
            }


            foreach (auto graphElement, graphs)
            {
                graphElement->updateValue();
            }


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

            setMoveLineRealTime(newValue);

        }
    }
}

void RealTimeQCP::beforeReplot()
{
    //WARNING update values without dependence of _line position
    //next fix here
    if (moveLineRealTime())
    {
        //TODO set to 1970 and don't move
        setCursorKey(currentDateTime());
    }
}

void RealTimeQCP::_setTimeAxisRange(const QCPRange &newRange)
{
    plot()->xAxis->setRange(newRange);
    auto delta = newRange.upper - newRange.lower;
    if (!EasyLiving::isEqualDouble(timeAxisOldRange, delta))
    {
        timeAxisOldRange = delta;
        updateTimeAxisLabel();
    }
}


void RealTimeQCP::_setCursorKey(double time)
{
    //BUG ?is this mouse move or regular move by timer?
    if (labelTime->isVisible())
        labelTime->setText(formatLabelTime(time));

    foreach (auto graphElement, graphs)
    {
        graphElement->moveCursor(time);
    }

    //    auto lower = getYAxisLower();
    //    auto upper = getYAxisUpper();
    auto lower = -999999;
    auto upper = +999999;


    _cursor->start->setCoords(time, lower);
    _cursor->end->setCoords(time, upper);

    //NOTE check cpu usage too big
    if(!realTime())
    {
        plot()->replot();
    }
}

void RealTimeQCP::setCursorKey(double time)
{
    _setCursorKey(time);
    emit cursorKeyChanged(time);

}


QString RealTimeQCP::formatLabelTime(double time)
{
    //TODO show MSEC ?formatTimeUi(true) and +07:00
    //auto mouseTimeQDT = QDateTime().fromString("1970-01-01T00:00:00", Qt::ISODate).addMSecs(static_cast<qint64>(time*1000));

    auto mouseTimeQDT = QDateTime::fromTime_t(static_cast<uint>(time));
    auto mouseTimeStr = mouseTimeQDT.toString(EasyLiving::formatTimeUi(false));

    if (cursor2Visible())
    {
        auto deltaTimeMSEC = _cursor->start->key() - _cursor2->start->key();
        bool negative = deltaTimeMSEC < 0;
        if (negative) deltaTimeMSEC *= -1;
        auto deltaTimeQT = QTime(0,0,0).addMSecs(static_cast<int>(deltaTimeMSEC*1000));
        auto result = QString("%1 [%2%3]").arg(mouseTimeStr).arg(negative ? "-" : "").arg(deltaTimeQT.toString(EasyLiving::formatTimeUi(false)));
        return result;
    }
    else
    {
        auto deltaTimeMSEC = QDateTime::currentDateTime().msecsTo(mouseTimeQDT);
        //qDebug() << deltaTimeMSEC;
        if (deltaTimeMSEC > -1000)
            return mouseTimeStr;

        auto deltaTimeQT = QTime(0,0,0);
        deltaTimeQT = deltaTimeQT.addMSecs(static_cast<int>(-deltaTimeMSEC));
        auto deltaTimeStr = deltaTimeQT.toString(EasyLiving::formatTimeUi(false));


        return QString("%1 (-%2)").arg(mouseTimeStr).arg(deltaTimeStr);
    }


}

bool RealTimeQCP::isInAxisRect(QPoint pos)
{
    return plot()->axisRect()->rect().contains(pos);
}
