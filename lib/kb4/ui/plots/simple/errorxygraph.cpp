#include "errorxygraph.h"



ErrorXYGraph::ErrorXYGraph(const QString &label, const QString &postfix, QColor color, QCustomPlot *qcp, QCPAxis *yAxis, int precision, bool scientificNotation)
    :ErrorYGraph(label, postfix, color, qcp, yAxis, precision, scientificNotation)
{
    errorBarsX = new QCPErrorBars(qcp->xAxis, yAxis);
    errorBarsX->removeFromLegend();
    errorBarsX->setDataPlottable(_graph);
    errorBarsX->setPen(errorBarsY->pen());
    errorBarsX->setErrorType(QCPErrorBars::etKeyError);
    //_errorBars->setBrush(color);
}

void ErrorXYGraph::addData(double x, double y, double errorBottom, double errorTop, double errorLeft, double errorRight)
{
    ErrorYGraph::addData(x, y, errorBottom, errorTop);
    errorsXLeft.append(errorLeft);
    errorsXRight.append(errorRight);

    errorBarsX->setData(errorsXLeft, errorsXRight);
}

QList<double> ErrorXYGraph::value(int index)
{
    QList<double> result;

    if (index > count())
    {
        qCritical() << EL_FORMAT_ERR("index is invalid");
        return result;
    }

    auto data = _graph->data()->at(index);
    auto errorY = errorBarsY->data()->at(index);
    auto errorX = errorBarsX->data()->at(index);
    result.append(data->key);
    result.append(data->value);
    result.append(errorX.errorPlus);
    result.append(errorX.errorMinus);
    result.append(errorY.errorPlus);
    result.append(errorY.errorMinus);

    return result;
}

void ErrorXYGraph::updateLegendItem()
{
    ErrorYGraph::updateLegendItem();
}

void ErrorXYGraph::abstractSetVisible()
{
    ErrorYGraph::abstractSetVisible();
    errorBarsX->setVisible(visible());
}

void ErrorXYGraph::abstractSetColor()
{
    ErrorYGraph::abstractSetColor();
    errorBarsX->setPen(color());
}
