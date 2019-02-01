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
    connect(this, &Graph::visibleChanged, _graphLegendItem, &GraphLegendItem::setVisibleValue);
    connect(_graphLegendItem, &GraphLegendItem::visibleChanged, this, &Graph::graphVisibleChanged);
    connect(_graphLegendItem, &GraphLegendItem::colorChanged, this, &Graph::colorChanged);

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
    setVisible(newValue, true);
}

void Graph::setVisible(bool newValue, bool emitSignal)
{
    //TODO autoscale without unsivible graphs
    _graph->setVisible(newValue);
    _tracer->setVisible(newValue);

    if (emitSignal)
    {
        emit visibleChanged(newValue);
    }

//    if (visible)
//    {

//    }
//    else
//    {
//        _plot->removeGraph(_graph);
    //    }
}

void Graph::setColor(QColor newColor)
{
    setColor(newColor, true);
}

void Graph::setColor(QColor newColor, bool emitSignal)
{

}




void Graph::graphVisibleChanged(bool newValue)
{
    setVisible(newValue, false);
}

void Graph::colorChanged(QColor newColor)
{
    color = newColor;
    _graph->setPen(color);

    _tracer->setBrush(color);
    _tracer->setPen(color);
}
