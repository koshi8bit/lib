#include "simplegraph.h"

SimpleGraph::SimpleGraph(const QString &label, const QString &postfix, QColor color, QCustomPlot *qcp, QCPAxis *yAxis, int precision, bool scientificNotation)
    :AbstractGraph(label, postfix, color, qcp, precision, scientificNotation)
{
    _yAxis = yAxis;
    _graph = qcp->addGraph(qcp->xAxis, yAxis);
    _graph->setName(label);

    _graph->setLineStyle(QCPGraph::LineStyle::lsNone);
    _graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 6));
    _graph->setAdaptiveSampling(true);

    _errorBars = new QCPErrorBars(qcp->xAxis, yAxis);
    _errorBars->removeFromLegend();
    _errorBars->setDataPlottable(_graph);

    QPen pen;
    pen.setColor(color);
    pen.setWidth(1);
    _graph->setPen(pen);
    _graph->setBrush(color);

    pen.setStyle(Qt::PenStyle::SolidLine);
    _errorBars->setPen(pen);
    //_errorBars->setBrush(color);
}

//SimpleGraph::~SimpleGraph()
//{

//}

void SimpleGraph::addData(double x, double y)
{
    if (_graph)
        _graph->addData(x, y);
}

void SimpleGraph::addData(double x, double y, double errorMin, double errorMax)
{
    addData(x, y);
    _errorBars->addData(errorMin, errorMax);
}

void SimpleGraph::updateLegendItem()
{
}

void SimpleGraph::abstractSetVisible()
{
    _graph->setVisible(visible());
    _errorBars->setVisible(visible());
}

void SimpleGraph::abstractSetColor()
{
    _graph->setPen(color());
    _graph->setBrush(color());

    _errorBars->setPen(color());
}
