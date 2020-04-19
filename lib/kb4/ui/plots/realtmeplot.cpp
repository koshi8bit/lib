#include "realtmeplot.h"

RealTmePlot::RealTmePlot(QWidget *parent)
    :AbstractPlot(parent)
{
    configurePlot();
}

RealTmePlot::~RealTmePlot()
{

}

void RealTmePlot::configurePlot()
{

//    connect(qcp(), &QCustomPlot::axisClick, this, &RealTmePlot::axisClick);
//    connect(qcp(), &QCustomPlot::axisDoubleClick, this, &RealTmePlot::axisDoubleClick);

//    //connect(plot(), &QCustomPlot::mouseMove, this, &RTPlotWithLegend::mouseMove);
//    connect(qcp(), SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));
//    connect(qcp(), &QCustomPlot::mousePress, this, &RealTmePlot::mousePress);
//    connect(qcp(), &QCustomPlot::mouseDoubleClick, this, &RealTmePlot::mouseDoubleClick);
//    connect(qcp(), &QCustomPlot::mouseWheel, this, &RealTmePlot::mouseWheel);
//    //connect(plot(), SIGNAL(mouseWheel(QMouseEvent*)), this, SLOT(mouseWheel(QMouseEvent*)));

//    connect(qcp(), &QCustomPlot::beforeReplot, this, &RealTmePlot::beforeReplot);
//    connect(qcp()->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(setTimeAxisRange(QCPRange)));

//    configureStatusLabel();
//    _configurePlot();
//    _setCursor2Visible(false);
//    updateStatusLabelFlag = true;

}

//void RealTmePlot::axisClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event)
//{
//    Q_UNUSED(axis)
//    Q_UNUSED(part)
//    if (event->button() == Qt::MouseButton::RightButton)
//    {
//        autoScaleAxis(axis);
//    }
//}

//void RealTmePlot::axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event)
//{
//    Q_UNUSED(part)
//    Q_UNUSED(event)
//    if (event->button() == Qt::MouseButton::LeftButton)
//    {
//        auto plot = static_cast<QCustomPlot *>(sender());
//        AxisConfig ac(axis, plot->xAxis == axis, this);
//        ac.setModal(true);
//        ac.exec();
//        plot->replot();
//    }
//}

//void RealTmePlot::mouseMove(QMouseEvent *event)
//{
//    if (isInAxisRect(event->pos()))
//    {

//    }
//    if (realTime() && moveLineRealTime())
//        return;

//    auto time = plot()->xAxis->pixelToCoord(event->x());
//    setCursorKey(time);
//}

//void RealTmePlot::mousePress(QMouseEvent *event)
//{
//    //configureAxesZoomAndDrag(isInAxisRect(event->pos()));
//    //qDebug() << isInAxisRect(event->pos());
//    if (isInAxisRect(event->pos()))
//    {
//        if (event->button() == Qt::MouseButton::RightButton)
//        {
//            setMoveLineRealTime(!moveLineRealTime());
//        }

//        if (event->button() == Qt::MouseButton::MiddleButton)
//        {
//            if (!cursor2Visible())
//            {
//                setCursor2Key(_cursor->start->key());
//            }
//            else
//            {
//                setCursor2Visible(false);
//            }


//            foreach (auto graphElement, _graphs)
//            {
//                graphElement->updateValue();
//            }


//        }

//    }
//}

//void RealTmePlot::mouseDoubleClick(QMouseEvent *event)
//{
//    if (isInAxisRect(event->pos()))
//    {
//        if (event->button() == Qt::MouseButton::LeftButton)
//        {
//            auto newValue = !realTime();
//            setRealTime(newValue);

//            setMoveLineRealTime(newValue);

//        }
//    }
//}

//void RealTmePlot::mouseWheel(QWheelEvent *event)
//{
//    qDebug() << "mouseWheel";
//    //configureAxesZoomAndDrag(isInAxisRect(event->pos()));
//    //qDebug() << isInAxisRect(event->pos());
//}

//void RealTmePlot::beforeReplot()
//{
//    //WARNING update values without dependence of _line position
//    //next fix here
//    if (moveLineRealTime())
//    {
//        //TODO set to 1970 and don't move
//        setCursorKey(currentDateTime());
//    }
//}

//void RealTmePlot::_setTimeAxisRange(const QCPRange &newRange)
//{
//    plot()->xAxis->setRange(newRange);
//    auto delta = newRange.upper - newRange.lower;
//    if (!EasyLiving::isEqualDouble(timeAxisOldRange, delta))
//    {
//        timeAxisOldRange = delta;
//        updateTimeAxisLabel();
//    }
//    updateStatusLabel();
//}

//void RealTmePlot::updateStatusLabel()
//{
//    if (updateStatusLabelFlag)
//    {
//        QString text;
//        if (realTime()) text.append("R ");
//        if (!moveLineRealTime()) text.append("C1 ");
//        if (cursor2Visible()) text.append("C2 ");
//        statusLabel->setText(text.trimmed());
//        statusLabel->setVisible(!text.isEmpty());
//    }
//}

//void RealTmePlot::_configurePlot()
//{
//    //WARNING dublicate configureAxesZoomAndDrag??
//    qcp()->setInteraction(QCP::iRangeZoom, true);
//    qcp()->setInteraction(QCP::iRangeDrag, true);

//    setRealTime(true);

//    //WARNING dublicate exec in setRealTime
//    //configureAxesZoomAndDrag(false);

//    configurePlotBackground();

//    configurePlotTimeAxis();
//    configurePlotLine();
//    setMoveLineRealTime(true);
//    plot()->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);
//    plot()->xAxis->setRangeUpper(RealTimeQCP::currentDateTime());
//    setTimeAxisRange(60);

//    // { Tests
//    //plot()->setNoAntialiasingOnDrag(true);
//    //plot()->setPlottingHint(QCP::phFastPolylines,true); // ?tima45 line from ethernet

//    // } Tests
//}

//void RealTmePlot::configureAxesZoomAndDrag(bool configureYAxises)
//{
//    auto axis = QList<QCPAxis*>()
//            << qcp()->yAxis
//            << qcp()->yAxis2;

//    Q_UNUSED(configureYAxises)
//    //if (configureTimeAxis)
//        axis << qcp()->xAxis;
//    qcp()->axisRect()->setRangeZoomAxes(axis);

////    auto zoom = QList<QCPAxis*>()
////            << plot()->xAxis;

////    if (configureYAxises)
////    {
////        zoom << plot()->yAxis
////             << plot()->yAxis2;
////    }

////    auto drag = QList<QCPAxis*>()
////            << plot()->yAxis
////            << plot()->yAxis2
////            << plot()->xAxis;

////    plot()->axisRect()->setRangeZoomAxes(zoom);
//    //    plot()->axisRect()->setRangeDragAxes(drag);
//}


//bool RealTmePlot::realTime() const
//{
//    return _realTime;
//}

//void RealTmePlot::setRealTime(bool newValue, RealTmePlot *senderWidget)
//{
//    if (senderWidget == this) { return; }

//    _setRealTime(newValue);
//}

//void RealTmePlot::setRealTime(bool realTime)
//{
//    _setRealTime(realTime);
//    emit realTimeChanged(realTime);
//}

//void RealTmePlot::_setRealTime(bool newValue)
//{
//    _realTime = newValue;
//    //configureAxesZoomAndDrag(!newValue);
//    configureAxesZoomAndDrag(true);
//    updateStatusLabel();
//}

//void RealTmePlot::_setCursor2Visible(bool newValue)
//{
//    _cursor2->setVisible(newValue);
//    foreach (auto graphElement, _graphs)
//    {
//        graphElement->setCursor2Visible(newValue);
//    }

//    if (labelTime->isVisible())
//        labelTime->setText(formatLabelTime(_cursor->start->key()));

//    updateStatusLabel();
//}

//void RealTmePlot::configureStatusLabel()
//{
//    statusLabel = new QCPItemText(qcp());
//    statusLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
//    statusLabel->setPositionAlignment(Qt::AlignRight|Qt::AlignBottom);
//    statusLabel->position->setCoords(1.0, 0.95); // lower right corner of axis rect

//    statusLabel->setTextAlignment(Qt::AlignLeft);
//    statusLabel->setFont(QFont(font().family(), 10));
//    statusLabel->setPadding(QMargins(2, 0, 2, 0));
//    statusLabel->setBrush(QColor("#C0C0C0"));
//    statusLabel->setVisible(false);
//}
