#include "realtimeqcp.h"
#include "ui_realtimeqcp.h"

RealTimeQCP::RealTimeQCP(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RealTimeQCP)
{
    ui->setupUi(this);
    ui->widgetToolTip->setVisible(false);

    connect(plot(), &QCustomPlot::axisClick, this, &RealTimeQCP::axisClick);
    connect(plot(), &QCustomPlot::axisDoubleClick, this, &RealTimeQCP::axisDoubleClick);

    //connect(plot(), &QCustomPlot::mouseMove, this, &RTPlotWithLegend::mouseMove);
    connect(plot(), SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));
    connect(plot(), &QCustomPlot::mousePress, this, &RealTimeQCP::mousePress);
    connect(plot(), &QCustomPlot::mouseDoubleClick, this, &RealTimeQCP::mouseDoubleClick);
    connect(plot(), &QCustomPlot::mouseWheel, this, &RealTimeQCP::mouseWheel);
    //connect(plot(), SIGNAL(mouseWheel(QMouseEvent*)), this, SLOT(mouseWheel(QMouseEvent*)));

    connect(plot(), &QCustomPlot::beforeReplot, this, &RealTimeQCP::beforeReplot);
    connect(plot()->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(setTimeAxisRange(QCPRange)));

    configureStatusLabel();
    configurePlot();
    configureLegend();
    _setCursor2Visible(false);
    //configureSplitter();
    updateStatusLabelFlag = true;

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

void RealTimeQCP::configureStatusLabel()
{
    statusLabel = new QCPItemText(plot());
    statusLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    statusLabel->setPositionAlignment(Qt::AlignRight|Qt::AlignBottom);
    statusLabel->position->setCoords(1.0, 0.95); // lower right corner of axis rect

    statusLabel->setTextAlignment(Qt::AlignLeft);
    statusLabel->setFont(QFont(font().family(), 10));
    statusLabel->setPadding(QMargins(2, 0, 2, 0));
    statusLabel->setBrush(QColor("#C0C0C0"));
    statusLabel->setVisible(false);
}

void RealTimeQCP::updateStatusLabel()
{
    if (updateStatusLabelFlag)
    {
        QString text;
        if (realTime()) text.append("R ");
        if (!moveLineRealTime()) text.append("C1 ");
        if (cursor2Visible()) text.append("C2 ");
        statusLabel->setText(text.trimmed());
        statusLabel->setVisible(!text.isEmpty());
    }
}



void RealTimeQCP::configurePlot()
{
    //WARNING dublicate configureAxesZoomAndDrag??
    plot()->setInteraction(QCP::iRangeZoom, true);
    plot()->setInteraction(QCP::iRangeDrag, true);

    setRealTime(true);

    //WARNING dublicate exec in setRealTime
    //configureAxesZoomAndDrag(false);

    configurePlotBackground();

    configurePlotTimeAxis();
    configurePlotLine();
    setMoveLineRealTime(true);
    plot()->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);
    plot()->xAxis->setRangeUpper(RealTimeQCP::currentDateTime());
    setTimeAxisRange(60);

    // { Tests
    //plot()->setNoAntialiasingOnDrag(true);
    //plot()->setPlottingHint(QCP::phFastPolylines,true); // ?tima45 line from ethernet

    // } Tests


}


void RealTimeQCP::_setRealTime(bool newValue)
{
    _realTime = newValue;
    configureAxesZoomAndDrag(!newValue);
    updateStatusLabel();
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

bool RealTimeQCP::dayStyle() const
{
    return _dayStyle;
}

QCPItemLine *RealTimeQCP::cursor2() const
{
    return _cursor2;
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

void RealTimeQCP::setTimeAxisRange(int newRangeMSEC)
{
    plot()->xAxis->setRangeLower(plot()->xAxis->range().upper - newRangeMSEC);
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
    return dateTimeToKey(QDateTime::currentDateTime());
}

double RealTimeQCP::dateTimeToKey(QDateTime dt)
{
    return dt.toTime_t() + static_cast<double>(dt.time().msec())/1000;
}

QDateTime RealTimeQCP::keyToDateTime(double key)
{
    return QDateTime::fromTime_t(static_cast<uint>(key));
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

    _graphs.append(graph);
    legendLayout->insertWidget(legendLayout->count()-1, graph->graphLegendItem());
    return graph;
}

void RealTimeQCP::removeGraphs()
{
    foreach(auto g , graphs())
    {
        g->deleteLater();
    }
    _graphs.clear();
    colorSetter.resetColors();
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
    foreach (auto graphElement, _graphs)
    {
        graphElement->setCursor2Visible(newValue);
    }

    if (labelTime->isVisible())
        labelTime->setText(formatLabelTime(_cursor->start->key()));

    updateStatusLabel();
}

void RealTimeQCP::_setCursor2Key(double key)
{
    foreach (auto graphElement, _graphs)
    {
        graphElement->moveCursor2(_cursor->start->key());
    }

    _cursor2->start->setCoords(key, _cursor->start->coords().y());
    _cursor2->end->setCoords(key, _cursor->end->coords().y());
    _setCursor2Visible(true);
    plot()->replot();
    updateStatusLabel();
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
    updateStatusLabel();
}

void RealTimeQCP::setMoveLineRealTime(bool newValue)
{
    _setMoveLineRealTime(newValue);
    emit moveLineRealTimeChanged(newValue);
}


void RealTimeQCP::configureAxesZoomAndDrag(bool configureYAxises)
{
//    auto axis = QList<QCPAxis*>()
//            << plot()->yAxis
//            << plot()->yAxis2;

//    Q_UNUSED(configureTimeAxis)
//    //if (configureTimeAxis)
//        axis << plot()->xAxis;

    auto zoom = QList<QCPAxis*>()
            << plot()->xAxis;

    if (configureYAxises)
    {
        zoom << plot()->yAxis
             << plot()->yAxis2;
    }

    auto drag = QList<QCPAxis*>()
            << plot()->yAxis
            << plot()->yAxis2
            << plot()->xAxis;

    plot()->axisRect()->setRangeZoomAxes(zoom);
    plot()->axisRect()->setRangeDragAxes(drag);


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
    //auto delta = plot()->xAxis->range().upper - plot()->xAxis->range().lower;
    auto begin = keyToDateTime(plot()->xAxis->range().upper);
    auto end = keyToDateTime(plot()->xAxis->range().lower);
    auto delta = EasyLiving::dateTimeDelta(begin, end, false);
    plot()->xAxis->setLabel(QString("%1 [%2]").arg(timeLabel).arg(delta));

    //  deleteLater
//    if (dayStyle())
//    {
//        auto dt = new QDateTime(QDate(0, 0, 0), QTime(0, 0, 0));

//    }
//    else
//    {
//        auto t = QTime(0, 0, 0).addSecs(static_cast<int>(delta));
//        plot()->xAxis->setLabel(QString("%1 [%2]").arg(timeLabel).arg(t.toString(EasyLiving::formatTimeUi(false))));
//    }

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

QVector<Graph *> RealTimeQCP::graphs() const
{
    return _graphs;
}

void RealTimeQCP::autoScaleAxis(QCPAxis *axis)
{
    axis->rescale(true);
    auto delta = (axis->range().upper - axis->range().lower)*0.05; // 5%
    axis->setRange(axis->range().lower - delta, axis->range().upper + delta);
}

void RealTimeQCP::setDayStyle(bool newValue, bool showTime)
{
    _dayStyle = newValue;
    if (dayStyle())
    {
        QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
        auto format = EasyLiving::formatDateUi();
        if (showTime)
            format.append("\n"+EasyLiving::formatTimeUi());
        dateTicker->setDateTimeFormat(format);
        plot()->xAxis->setTicker(dateTicker);

        setRealTime(false);

        foreach(auto g, _graphs)
        {
            g->graph()->setLineStyle(QCPGraph::lsLine);
//            g->graph()->setLineStyle(QCPGraph::lsNone);
//            g->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
        }
    }
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
        plot->replot();
    }
}

void RealTimeQCP::mouseMove(QMouseEvent *event)
{
    if (isInAxisRect(event->pos()))
    {

    }
    if (realTime() && moveLineRealTime())
        return;

    auto time = plot()->xAxis->pixelToCoord(event->x());
    setCursorKey(time);
}

void RealTimeQCP::mousePress(QMouseEvent *event)
{
    //configureAxesZoomAndDrag(isInAxisRect(event->pos()));
    //qDebug() << isInAxisRect(event->pos());
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


            foreach (auto graphElement, _graphs)
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

void RealTimeQCP::mouseWheel(QWheelEvent *event)
{
    qDebug() << "mouseWheel";
    //configureAxesZoomAndDrag(isInAxisRect(event->pos()));
    //qDebug() << isInAxisRect(event->pos());
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
    updateStatusLabel();
}


void RealTimeQCP::_setCursorKey(double time)
{
    //BUG ?is this mouse move or regular move by timer?
    if (labelTime->isVisible())
        labelTime->setText(formatLabelTime(time));

    foreach (auto graphElement, _graphs)
    {
        graphElement->moveCursor(time);
    }

    //    auto lower = getYAxisLower();
    //    auto upper = getYAxisUpper();
    auto lower = -9999999999;
    auto upper = +9999999999;


    _cursor->start->setCoords(time, lower);
    _cursor->end->setCoords(time, upper);

    //NOTE check cpu usage too big
    //NOTE inf loop
//    if(!realTime())
//    {
//        plot()->replot();
//    }
}

void RealTimeQCP::setCursorKey(double time)
{
    _setCursorKey(time);
    emit cursorKeyChanged(time);

}


QString RealTimeQCP::formatLabelTime(double key)
{
    //TODO show MSEC ?formatTimeUi(true) and +07:00
    //auto mouseTimeQDT = QDateTime().fromString("1970-01-01T00:00:00", Qt::ISODate).addMSecs(static_cast<qint64>(time*1000));

    auto mouseTimeQDT = keyToDateTime(key);
    auto mouseTimeStr = mouseTimeQDT.toString(EasyLiving::formatTimeUi(false));

    if (dayStyle())
    {
        return mouseTimeQDT.toString(EasyLiving::formatDateTimeUi());
    }

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
        if (deltaTimeMSEC > -1000 )
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

void RealTimeQCP::on_pushButtonPrintScreen_clicked()
{
    PrintScreener::save(this);
}

void RealTimeQCP::on_pushButtonHelp_clicked()
{
    QMessageBox::about(this, "Help", ui->widgetToolTip->toolTip());
}
