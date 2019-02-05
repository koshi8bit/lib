#include "graph.h"


Graph::Graph(const QString &label, QColor color, QCustomPlot *plot, QCPAxis *yAxis, QObject *parent)
    : QObject(parent)
{
    _plot = plot;
    _yAxis = yAxis;

    _graph = plot->addGraph(plot->xAxis, yAxis);
    _graph->setName(label);
    _graph->setPen(color);
    //_graph->setLineStyle(QCPGraph::LineStyle::lsStepRight);


    _tracer = new QCPItemTracer(plot);
    _tracer->setGraph(_graph);
    _tracer->setInterpolating(true);
    _tracer->setStyle(QCPItemTracer::tsCircle);
    _tracer->setPen(_graph->pen());
    _tracer->setBrush(color);
    _tracer->setSize(5);

    _graphLegendItem = new GraphLegendItem(label, color);
    connect(_graphLegendItem, &GraphLegendItem::visibleChanged, this, &Graph::setVisibleByWidget);

}

Graph::~Graph()
{
    //FIXME exception
    //_graph->deleteLater();
    //_tracer->deleteLater();

    //_graphLegendItem->deleteLater();
}

QCPItemTracer *Graph::tracer()
{
    return _tracer;
}

QCPGraph *Graph::graph()
{
    return _graph;
}

GraphLegendItem *Graph::graphLegendItem()
{
    return _graphLegendItem;
}

void Graph::addData(double key, double value)
{
    _graph->addData(key, value);
}

double Graph::value()
{
    return _value;
}

void Graph::setGraphKey(double key)
{
    _tracer->setGraphKey(key);
    _value = _tracer->position->value();
    _graphLegendItem->setValue(_value);
}

void Graph::setVisible(bool newValue)
{
    //TODO autoscale without unsivible graphs
    _graph->setVisible(newValue);
    _tracer->setVisible(newValue);
    _graphLegendItem->setVisible(newValue);
}

void Graph::setVisibleByWidget(bool newValue)
{
    _graph->setVisible(newValue);
    _tracer->setVisible(newValue);
    emit visibleChanged(newValue);
}

