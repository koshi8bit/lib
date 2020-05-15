#include "simpleplot.h"

SimplePlot::SimplePlot(QWidget *parent)
    :AbstractPlot(parent)
{
    configurePlot();
}

SimpleGraph *SimplePlot::addGraph(const QString &label, const QString &postfix, bool yAxis2, int precision, bool scientificNotation)
{
    auto graph = new SimpleGraph(label,
                                 postfix,
                                 colorSetter.getColor(),
                                 qcp(),
                                 yAxis2 ? qcp()->yAxis2 : qcp()->yAxis,
                                 precision,
                                 scientificNotation);
    addAbstractGraph(graph);
    return graph;
}

ErrorYGraph *SimplePlot::addGraphErrorY(const QString &label, const QString &postfix, bool yAxis2, int precision, bool scientificNotation)
{
    auto graph = new ErrorYGraph(label,
                                 postfix,
                                 colorSetter.getColor(),
                                 qcp(),
                                 yAxis2 ? qcp()->yAxis2 : qcp()->yAxis,
                                 precision,
                                 scientificNotation);
    addAbstractGraph(graph);
    return graph;
}

ErrorXYGraph *SimplePlot::addGraphErrorXY(const QString &label, const QString &postfix, bool yAxis2, int precision, bool scientificNotation)
{
    auto graph = new ErrorXYGraph(label,
                                 postfix,
                                 colorSetter.getColor(),
                                 qcp(),
                                 yAxis2 ? qcp()->yAxis2 : qcp()->yAxis,
                                 precision,
                                 scientificNotation);
    addAbstractGraph(graph);
    return graph;
}

void SimplePlot::configureAxis(bool yAxis2, const QString &label, const QString &postfix, double min, double max, int precision, QCPAxis::ScaleType scaleType)
{
    configureAxis(yAxis2 ? qcp()->yAxis2 : qcp()->yAxis,
                  label,
                  postfix,
                  min,
                  max,
                  precision,
                  scaleType);
}

void SimplePlot::configureAxis(QCPAxis *axis, const QString &label, const QString &postfix, double min, double max, int precision, QCPAxis::ScaleType scaleType)
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
}

void SimplePlot::configurePlot()
{
    qcp()->setInteraction(QCP::iRangeZoom, true);
    qcp()->setInteraction(QCP::iRangeDrag, true);
    configurePlotBackground(true);
}

void SimplePlot::setAxisType(QCPAxis *axis, QCPAxis::ScaleType scaleType)
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
