#include "graphelement.h"


GraphElement::GraphElement(const QString &label, QColor color, QCustomPlot *plot, QCPAxis *yAxis, QObject *parent)
    : QObject(parent)
{
    _graph = plot->addGraph(plot->xAxis, yAxis);
    _graph->setName(label);
    _graph->setPen(color);


    _tracer = new QCPItemTracer(plot);
    _tracer->setGraph(_graph);
    _tracer->setInterpolating(true);
    _tracer->setStyle(QCPItemTracer::tsCircle);
    _tracer->setPen(_graph->pen());
    _tracer->setBrush(color);
    _tracer->setSize(5);

    //_graphLegendItem = new GraphLegendItem(label, color, plot);
    _graphLegendItem = new GraphLegendItem(label, color);
    connect(_graphLegendItem, &GraphLegendItem::visibleChanged, this, &GraphElement::visibleChanged);

}

GraphElement::~GraphElement()
{
    _graph->deleteLater();
    _tracer->deleteLater();
    //_graphLegendItem->deleteLater();
}

QCPItemTracer *GraphElement::tracer()
{
    return _tracer;
}

QCPGraph *GraphElement::graph()
{
    return _graph;
}

GraphLegendItem *GraphElement::graphLegendItem()
{
    return _graphLegendItem;
}

void GraphElement::addData(double key, double value)
{
    _graph->addData(key, value);
}

void GraphElement::setGraphKey(double key)
{
    _tracer->setGraphKey(key);
    _graphLegendItem->setValue(_tracer->position->value());
}

void GraphElement::visibleChanged(bool newValue)
{
    visible = newValue;
    _graph->setVisible(visible);
    _tracer->setVisible(visible);
}
