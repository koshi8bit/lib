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

    //_graphLegendItem = new GraphLegendItem(label, color, plot);
    _graphLegendItem = new GraphLegendItem(label, color);
    connect(_graphLegendItem, &GraphLegendItem::visibleChanged, this, &Graph::visibleChanged);
    connect(_graphLegendItem, &GraphLegendItem::colorChanged, this, &Graph::colorChanged);

}

Graph::~Graph()
{
    _graph->deleteLater();
    _tracer->deleteLater();
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

void Graph::setGraphKey(double key)
{
    _tracer->setGraphKey(key);
    _graphLegendItem->setValue(_tracer->position->value());
}

void Graph::visibleChanged(bool newValue)
{
    //TODO autoscale without unsivible graphs
    visible = newValue;

    _graph->setVisible(visible);
    _tracer->setVisible(visible);

//    if (visible)
//    {

//    }
//    else
//    {
//        _plot->removeGraph(_graph);
//    }
}

void Graph::colorChanged(QColor newColor)
{
    color = newColor;
    _graph->setPen(color);

    _tracer->setBrush(color);
    _tracer->setPen(color);
}
