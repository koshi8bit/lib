#include "errorxygraph.h"



ErrorXYGraph::ErrorXYGraph(const QString &label, const QString &postfix, QColor color, QCustomPlot *qcp, QCPAxis *yAxis, int precision, bool scientificNotation)
    :ErrorYGraph(label, postfix, color, qcp, yAxis, precision, scientificNotation)
{
    _errorBarsX = new QCPErrorBars(qcp->xAxis, yAxis);
    _errorBarsX->removeFromLegend();
    _errorBarsX->setDataPlottable(_graph);
    _errorBarsX->setPen(_errorBarsY->pen());
    _errorBarsX->setErrorType(QCPErrorBars::etKeyError);
    //_errorBars->setBrush(color);
}

void ErrorXYGraph::addData(double x, double y, double errorBottom, double errorTop, double errorLeft, double errorRight)
{
    ErrorYGraph::addData(x, y, errorBottom, errorTop);
    _errorBarsX->addData(errorLeft, errorRight);
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
    auto errorY = _errorBarsY->data()->at(index);
    auto errorX = _errorBarsX->data()->at(index);
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
    _errorBarsX->setVisible(visible());
}

void ErrorXYGraph::abstractSetColor()
{
    ErrorYGraph::abstractSetColor();
    _errorBarsX->setPen(color());
}
