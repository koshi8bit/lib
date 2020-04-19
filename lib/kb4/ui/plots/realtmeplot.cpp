#include "realtmeplot.h"

RealTmePlot::RealTmePlot(QWidget *parent)
    :AbstractPlot(parent)
{
    configurePlot();
}

void RealTmePlot::configurePlot()
{

    connect(qcp(), &QCustomPlot::axisClick, this, &RealTmePlot::axisClick);
    connect(qcp(), &QCustomPlot::axisDoubleClick, this, &RealTmePlot::axisDoubleClick);

    //connect(plot(), &QCustomPlot::mouseMove, this, &RTPlotWithLegend::mouseMove);
    connect(qcp(), SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));
    connect(qcp(), &QCustomPlot::mousePress, this, &RealTmePlot::mousePress);
    connect(qcp(), &QCustomPlot::mouseDoubleClick, this, &RealTmePlot::mouseDoubleClick);
    connect(qcp(), &QCustomPlot::mouseWheel, this, &RealTmePlot::mouseWheel);
    //connect(plot(), SIGNAL(mouseWheel(QMouseEvent*)), this, SLOT(mouseWheel(QMouseEvent*)));

    connect(qcp(), &QCustomPlot::beforeReplot, this, &RealTmePlot::beforeReplot);
    connect(qcp()->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(setTimeAxisRange(QCPRange)));

}

void RealTmePlot::axisClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event)
{
    Q_UNUSED(axis)
    Q_UNUSED(part)
    if (event->button() == Qt::MouseButton::RightButton)
    {
        autoScaleAxis(axis);
    }
}

void RealTmePlot::axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event)
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

void RealTmePlot::mouseMove(QMouseEvent *event)
{
    if (isInAxisRect(event->pos()))
    {

    }
    if (realTime() && moveLineRealTime())
        return;

    auto time = plot()->xAxis->pixelToCoord(event->x());
    setCursorKey(time);
}

void RealTmePlot::mousePress(QMouseEvent *event)
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

void RealTmePlot::mouseDoubleClick(QMouseEvent *event)
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

void RealTmePlot::mouseWheel(QWheelEvent *event)
{
    qDebug() << "mouseWheel";
    //configureAxesZoomAndDrag(isInAxisRect(event->pos()));
    //qDebug() << isInAxisRect(event->pos());
}

void RealTmePlot::beforeReplot()
{
    //WARNING update values without dependence of _line position
    //next fix here
    if (moveLineRealTime())
    {
        //TODO set to 1970 and don't move
        setCursorKey(currentDateTime());
    }
}

void RealTmePlot::_setTimeAxisRange(const QCPRange &newRange)
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
