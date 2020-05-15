#include "errorygraph.h"


ErrorYGraph::ErrorYGraph(const QString &label, const QString &postfix, QColor color, QCustomPlot *qcp, QCPAxis *yAxis, int precision, bool scientificNotation)
    :SimpleGraph(label, postfix, color, qcp, yAxis, precision, scientificNotation)
{
    auto pen = _graph->pen();
    pen.setStyle(Qt::PenStyle::SolidLine);

    _errorBarsY = new QCPErrorBars(qcp->xAxis, yAxis);
    _errorBarsY->removeFromLegend();
    _errorBarsY->setDataPlottable(_graph);
    _errorBarsY->setPen(pen);
    _errorBarsY->setErrorType(QCPErrorBars::etValueError);
    //_errorBars->setBrush(color);
}

void ErrorYGraph::addData(double x, double y, double errorBottom, double errorTop)
{
    SimpleGraph::addData(x, y);
    _errorBarsY->addData(errorBottom, errorTop);
}

void ErrorYGraph::updateLegendItem()
{
    SimpleGraph::updateLegendItem();
}

void ErrorYGraph::abstractSetVisible()
{
    SimpleGraph::abstractSetVisible();
    _errorBarsY->setVisible(visible());
}

void ErrorYGraph::abstractSetColor()
{
    SimpleGraph::abstractSetColor();
    _errorBarsY->setPen(color());
}
