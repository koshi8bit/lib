#include "graphelement.h"


GraphElement::GraphElement(const QString &label, QColor color, QCustomPlot *plot, QCPAxis *yAxis, QObject *parent)
    : QObject(parent)
{
    graph = plot->addGraph(plot->xAxis, yAxis);
    graph->setName(label);
    graph->setPen(color);

    _tracer = new QCPItemTracer(plot);
    _tracer->setGraph(graph);
    _tracer->setInterpolating(true);
    _tracer->setStyle(QCPItemTracer::tsCircle);
    _tracer->setPen(graph->pen());
    _tracer->setBrush(color);
    _tracer->setSize(5);

}

GraphElement::~GraphElement()
{
    graph->deleteLater();
    _tracer->deleteLater();
}

QCPItemTracer *GraphElement::tracer()
{
    return _tracer;
}
