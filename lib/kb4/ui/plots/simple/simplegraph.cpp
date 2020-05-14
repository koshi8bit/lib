#include "simplegraph.h"

SimpleGraph::SimpleGraph(const QString &label, const QString &postfix, QColor color, QCustomPlot *qcp, QCPAxis *yAxis, int precision, bool scientificNotation)
    :AbstractGraph(label, postfix, color, qcp, precision, scientificNotation)
{

}

SimpleGraph::~SimpleGraph()
{

}

void SimpleGraph::updateLegendItem()
{

}

void SimpleGraph::abstractSetVisible()
{

}

void SimpleGraph::abstractSetColor()
{

}
